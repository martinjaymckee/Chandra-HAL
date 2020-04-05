#ifndef CHANDRA_LCD_H
#define CHANDRA_LCD_H

#include <chrono>
#include "chrono.h"
#include "gpio.h"
#include "stream.h"

namespace chandra
{
namespace drivers
{
using namespace std::literals::chrono_literals;

namespace modifiers
{
struct Position
{
  size_t row;
  size_t column;
};
} /*namespace modifiers*/

template<uint8_t Rows, uint8_t Columns>
class CharacterLCD : public Stream<CharacterLCD<Rows, Columns>>
{
  protected:
    using io_t = chandra::io::IO;

    enum lcd_mode_t {
        FourBit,
        EightBit
    };

    struct Pos
    {
      uint8_t row;
      uint8_t column;
    };

  public:
    enum cursor_mode_t {
      CursorOff,
      CursorLine,
      CursorBlock
    };

    // Construct in 8-bit mode
    CharacterLCD( const io_t& _RS, const io_t _E,
      const io_t& _D7, const io_t& _D6, const io_t& _D5, const io_t& _D4,
      const io_t& _D3, const io_t& _D2, const io_t& _D1, const io_t& _D0,
      const io_t& _RW = io_t{})
      : mode_{EightBit}, RS(_RS), E(_E),
        D{
          _D0, _D1, _D2, _D3,
          _D4, _D5, _D6, _D7
        },
        RW(_RW)
    {}

    // Construct in 4-bit mode
    CharacterLCD( const io_t& _RS, const io_t _E,
      const io_t& _D7, const io_t& _D6, const io_t& _D5, const io_t& _D4,
      const io_t& _RW = io_t{})
      : mode_{FourBit}, RS(_RS), E(_E),
        D{
          {}, {}, {}, {},
          _D4, _D5, _D6, _D7
        },
        RW(_RW)
    {}

    bool init() {
      RS.output(true);
      RS = false;
      E.output(true);
      E = false;
      if(RW.valid()) {
        RW.output(true);
        RW = false;
      }

      for(auto& io: D) {
        io.output(true);
        io = false;
      }

      switch(mode_) {
        case FourBit:
          enterFourBitMode();
          break;

        case EightBit:
          enterEightBitMode();
          break;
      }

      display(true);

      return true;
    }

    bool home() {
      instruction(0x02);
      chandra::chrono::delay(2ms);
      return true;
    }

    bool clear() {
      instruction(0x01);
      chandra::chrono::delay(2ms);
      return true;
    }

    bool pos(const uint8_t& _row, const uint8_t& _column) {
      if(_row >= Rows or _column >= Columns) return false;
      const uint8_t addr =  row_addr(_row) + _column;
      instruction(0x80|addr);
      cur_pos_.row = _row;
      cur_pos_.column = _column;
      return true;
    }

    bool put(char _ch, bool _raw = false) {
      if(!_raw) {
        if(_ch == '\n') {
          return newline();
        }
      }
      const bool success = data(_ch);
      cur_pos_ = advance_position(cur_pos_, 1);
      return success;
		}

    bool display(bool _visible) {
      display_visible_ = _visible;
      updateVisibility();
      return true;
    }

    bool cursor(bool _visible) {
      cursor_visible_ = _visible;
      updateVisibility();
      return true;
    }

    bool cursor(bool _visible, bool _blink) {
      cursor_blink_ = _blink;
      return cursor(_visible);
    }

		// bool puts( const char* _str ) { // OPTIMIZE
		// 	while( *_str ) {
		// 		put(*_str);
		// 		++_str;
		// 	}
		// 	return true;
		// }


    bool newline() {
      const uint8_t new_row = (cur_pos_.row+1)%Rows;
      return pos(new_row, 0);
    }

  protected:
    constexpr uint8_t row_addr(const uint8_t _row) {
        switch(_row) {
          default:
          case 0:
            return 0x00;

          case 1:
            return 0x40;

          case 2:
            return (Columns==16) ? 0x10 : 0x14;

          case 3:
            return (Columns==16) ? 0x50 : 0x54;
        }
        return 0;
    }

    bool strobe() {
        E = true;
        chandra::chrono::delay(1us);
        E = false;
        chandra::chrono::delay(1us);
        return true;
    }

    bool command(uint8_t _cmd, bool rs) {
      RS = rs;

      switch(mode_) {
        case FourBit:
          write4bit(_cmd>>4);
          strobe();
          write4bit(_cmd&0x0F);
          strobe();
          break;

        case EightBit:
          write8bit(_cmd);
          strobe();
          break;
      }

      chandra::chrono::delay(100us);

      return true;
    }

    bool data(uint8_t _val) { return command(_val, true); }
    bool instruction(uint8_t _cmd) { return command(_cmd, false); }

    bool updateVisibility() {
        const uint8_t visibility_cmd = 0x08 |
                                        (display_visible_ ? 0x04 : 0x00) |
                                        (cursor_visible_ ? 0x02 : 0x00) |
                                        (cursor_blink_ ? 0x1 : 0x00);
       instruction(visibility_cmd);
       return true;
    }

    bool enterFourBitMode() {
      chandra::chrono::delay(15ms);
      write4bit(0x3);
      strobe();
      chandra::chrono::delay(5ms);
      write4bit(0x3);
      strobe();
      chandra::chrono::delay(100us);
      write4bit(0x2);
      strobe();
      chandra::chrono::delay(100us);
      return true;
    }

    bool enterEightBitMode() {
      return true;
    }

    bool write_impl(uint8_t _val, uint8_t _base, uint8_t _count) {
      uint8_t mask = 0x01;
      for(uint8_t offset = 0; offset < _count; ++offset) {
        D[_base+offset] = bool(_val&mask);
        mask <<= 1;
      }
      return true;
    }

    bool write4bit(uint8_t _val) { return write_impl(_val, 4, 4); }

    uint8_t read4bit() const {
      return 0;
    }

    bool write8bit(uint8_t _val) { return write_impl(_val, 0, 8); }

    uint8_t read8bit() const {
      return 0;
    }

    constexpr Pos advance_position(const Pos& _pos, uint8_t _adv) const {
      // TODO: THIS IS LIKELY TO BE VERY SLOW.  LOOK INTO MAKING THIS MORE EFFICIENT
      const uint32_t idx = (_pos.row * Columns + _pos.column) + _adv;
      const uint8_t row = (idx / Columns) % Rows;
      const uint8_t column = idx % Columns;
      return {row, column};
    }

  private:
    bool display_visible_;
    bool cursor_visible_;
    bool cursor_blink_;
    lcd_mode_t mode_;
    io_t RS;
    io_t E;
    io_t D[8];
    io_t RW;
    Pos cur_pos_;
};

} /*namespace drivers*/
} /*namspace chandra*/
#endif /*CHANDRA_LCD_H*/
