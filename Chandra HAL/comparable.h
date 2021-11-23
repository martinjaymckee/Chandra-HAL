#ifndef CHANDRA_COMPARABLE_H
#define CHANDRA_COMPARABLE_H

namespace chandra
{
namespace math{

class Comparable
{
  public:
    template<class T>
    bool operator > (const T&) const {
      return false;
    }

    template<class T>
    bool operator < (const T& _v) const {
      return (!this->operator >(_v)) and (!this->operator ==(_v));
    }

    template<class T>
    bool operator >= (const T& _v) const {
      return (this->operator >(_v)) and (this->operator ==(_v));
    }

    template<class T>
    bool operator <= (const T& _v) const {
      return !this->operator >(_v);
    }

    template<class T>
    bool operator == (const T& _v) const {
      return false;
    }

    template<class T>
    bool operator != (const T& _v) const {
      return !this->operator ==(_v);
    }
};

}
}

#endif /* CHANDRA_COMPARABLE_H */
