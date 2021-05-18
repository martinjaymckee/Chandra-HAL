#!/usr/bin/env python
# -*- coding: utf-8 -*-

import fractions
from mako.template import Template

file_template = Template(
"""
#ifndef CHANDRA_${system.upper()}_UNITS_H
#define CHANDRA_${system.upper()}_UNITS_H

#include <ratio>

#include "dimensions.h"
#include "quantity.h"

namespace chandra
{
namespace units
{
namespace ${system}
{
${units}
} /*namespace ${system}*/
} /*namespace units*/
} /*namespace chandra*/
#endif /*CHANDRA_${system.upper()}_UNITS_H*/
""")

unit_template = Template(
"""
//
// Unit "${symbol}"
//
    struct ${symbol}
    {
        using factor_t = std::ratio<${num}, ${den}>; // ${factor}
        using dimensions_t = ${dimensions};
        using offset_t = std::ratio<${offset_num}, ${offset_den}>;
        using relative_t = ${rel_symbol};
        static constexpr bool absolute = ${'true' if absolute else 'false'};
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "${symbol}";
        }
    };
    template<typename Value = long double>
    using Q_${symbol} = units::Quantity<Value, ${symbol}>;
    namespace literals
    {
        static inline Q_${symbol}<long double> operator "" _${symbol}_ (long double _v) {
            return Q_${symbol}<long double>(_v); }
        static inline Q_${symbol}<long double> operator "" _${symbol}_ (unsigned long long int _v) {
            return Q_${symbol}<long double>(static_cast<long double>(_v)); }
    }
""")

class UnitsContext:
    def __init__(self):
        self.units = []
        self.names = {}
        self.system = None
        self.let = {}
        self.default_tolerance = 1e-4
        self.param_limit = int(1e18)


def PrefixedUnits(symbol, dimensions, factor, offset=None, power=1, param_limit=1e18, tol=1e-6):
    return_units = []
    prefixes = [
        ('E', fractions.Fraction(1000000000000000000)),
        ('P', fractions.Fraction(1000000000000000)),
        ('T', fractions.Fraction(1000000000000)),
        ('G', fractions.Fraction(1000000000)),
        ('M', fractions.Fraction(1000000)),
        ('k', fractions.Fraction(1000)),
        ('h', fractions.Fraction(100)),
        ('da', fractions.Fraction(10)),
        ('', fractions.Fraction(1)),
        ('d', fractions.Fraction(1,10)),
        ('c', fractions.Fraction(1,100)),
        ('m', fractions.Fraction(1,1000)),
        ('u', fractions.Fraction(1,1000000)),
        ('n', fractions.Fraction(1,1000000000)),
        ('p', fractions.Fraction(1,1000000000000)),
        ('f', fractions.Fraction(1,1000000000000000)),
        ('a', fractions.Fraction(1,1000000000000000000))
    ]

    for prefix, mult in prefixes:
        prefixed_symbol = prefix + symbol
        factor = fractions.Fraction(factor)
        scaled_factor = mult*factor
        return_units += Unit(prefixed_symbol, dimensions, scaled_factor, offset, power)
    return return_units


class FactorValue:
    def __init__(self, value, sig_digits=None, min_sig_digits=4):
        self.__value = None
        self.__value = float(value)
        self.__sig_digits = 0
        if sig_digits is None and isinstance(value, str):
            self.__sig_digits = self.__get_sig_digits(value)
        else:
            self.__sig_digits = sig_digits
        self.__sig_digits = max(self.__sig_digits, min_sig_digits)

    def __str__(self):
        return '{}(sig_digits = {}, tol = {:g})'.format(self.value, self.sig_digits, self.tolerance)

    def __float__(self):
        return self.value

    def __mul__(self, arg):
        return FactorValue(arg*self.__value, self.__sig_digits)

    def __rmul__(self, arg):
        return FactorValue(arg*self.__value, self.__sig_digits)

    def __pow__(self, exp):
        return FactorValue(self.__value**exp, self.__sig_digits)

    @property
    def value(self): return self.__value

    @property
    def sig_digits(self): return self.__sig_digits

    @property
    def tolerance(self): return 10**(-self.sig_digits)

    def __get_sig_digits(self, value):
        value = value.lower()
        sig_digits = 0
        if value.find('e') == -1:
            integer, _, fractional = value.partition('.') # TODO: THIS SHOULD BE LOCALIZED TO USE OTHER RADIX POINTS!
            if not len(integer) == 0 and not int(integer) == 0:
                sig_digits = len(integer) + len(fractional)
            else:
                fractional = fractional.lstrip('0')
                sig_digits = len(fractional)
        else:
            mantissa, _, _ = value.partition('e')
            mantissa = mantissa.strip()
            sig_digits = len(mantissa)
        return sig_digits


class ContextCommand:
    def __init__(self, name, value):
        self.__name = name
        self.__value = value

    def __call__(self, ctx):
        name = self.__name
        value = self.__value
        if name == 'system':
            assert ctx.system is None, 'Error: Only a single units system supported now!'
            ctx.system = value
            if not ctx.system in ctx.names:
                ctx.names[ctx.system] = set()
        if name == 'tolerance':
            ctx.default_tolerance = float(value)


class LetDeclaration:
    def __init__(self, system, name, value):
        self.__system = system
        self.__name = name
        self.__value = value

    def __str__(self):
        return 'let {}::{} = {}'.format(self.system, self.name, self.value)

    @property
    def system(self): return self.__system

    @property
    def name(self): return self.__name

    @property
    def value(self): return self.__value


class UnitCommand:
    def __init__(self, dimensions, symbol, factor, power, offset, message):
        self.__dimensions = dimensions
        self.__symbol = symbol
        self.__factor = factor
        self.__power = power
        self.__offset = offset
        self.__absolute = not offset is None
        self.__message = message

    def __call__(self, ctx):
        units = []
        factor = self.__get_value(self.__factor, ctx)
        offset = self.__get_value(self.__offset, ctx)
        power = 1 if self.__power is None else self.__power
        prefixed, symbol = self.__parse_symbol(self.__symbol, ctx)
        if prefixed:
            units += self.__prefixed_units(symbol, self.__dimensions, factor, offset, power, ctx)
        else:
            units += self.__unit(symbol, self.__dimensions, factor, offset, power, ctx)
        return units

    def __prefixed_units(self, symbol, dimensions, factor, offset, power, ctx):
        return_units = []
        prefixes = [
            ('E', fractions.Fraction(1000000000000000000)),
            ('P', fractions.Fraction(1000000000000000)),
            ('T', fractions.Fraction(1000000000000)),
            ('G', fractions.Fraction(1000000000)),
            ('M', fractions.Fraction(1000000)),
            ('k', fractions.Fraction(1000)),
            ('h', fractions.Fraction(100)),
            ('da', fractions.Fraction(10)),
            ('', fractions.Fraction(1)),
            ('d', fractions.Fraction(1,10)),
            ('c', fractions.Fraction(1,100)),
            ('m', fractions.Fraction(1,1000)),
            ('u', fractions.Fraction(1,1000000)),
            ('n', fractions.Fraction(1,1000000000)),
            ('p', fractions.Fraction(1,1000000000000)),
            ('f', fractions.Fraction(1,1000000000000000)),
            ('a', fractions.Fraction(1,1000000000000000000))
        ]

        for prefix, mult in prefixes:
            prefixed_symbol = prefix + symbol
            scaled_factor = mult*factor
            return_units += self.__unit(prefixed_symbol, dimensions, scaled_factor, offset, power, ctx)
        return return_units

    def __unit(self, symbol, dimensions, factor, offset, power, ctx):
        units = []
        if not symbol in ctx.names[ctx.system]:
            factor = factor**power
            factor_txt = "{:g}".format(float(factor))
            factor, factor_tol = self.__fractionize(factor, ctx)
            offset, offset_tol = self.__fractionize(offset, ctx)
            if (not factor is None) and (not offset is None):
                max_param = max(factor.numerator, factor.denominator)
                if max_param <= ctx.param_limit and factor != 0:
                    unit_text = unit_template.render(
                        symbol=symbol,
                        rel_symbol=symbol,
                        absolute=False,
                        num=factor.numerator,
                        den=factor.denominator,
                        factor=factor_txt,
                        dimensions="dimensions::{}".format(dimensions),
                        offset_num=0,
                        offset_den=1
                    )
                    ctx.units.append( (ctx.system, symbol, unit_text) ) # DO SOMETHING TO ARRANGE THESE....
                    ctx.names[ctx.system].add(symbol)
                    units.append(unit_text)
                    if self.__absolute:
                        unit_text = unit_template.render(
                            symbol=symbol+'_abs',
                            rel_symbol=symbol,
                            absolute=True,
                            num=factor.numerator,
                            den=factor.denominator,
                            factor=factor_txt,
                            dimensions="dimensions::{}".format(dimensions),
                            offset_num=offset.numerator,
                            offset_den=offset.denominator
                        )
                        ctx.units.append( (ctx.system, symbol, unit_text) ) # DO SOMETHING TO ARRANGE THESE....
                        ctx.names[ctx.system].add(symbol)
                        units.append(unit_text)
            else:
                print("Unable to create {} (factor = {})".format(symbol, factor))
        else:
            assert False, "Attempting to readd unit {}".format(symbol)
        return units

    def __parse_symbol(self, symbol, ctx): # TODO: VALIDATE THE REDUCED SYMBOL AS AN IDENTIFIER
        symbol = symbol.strip()
        if symbol[0] == '*':
            return True, symbol[1:]
        return False, symbol

    def __fractionize(self, value, ctx):
        if value is None: return fractions.Fraction(), ctx.default_tolerance
        denom_limit = 10
        tolerance = min(value.tolerance, ctx.default_tolerance)
        value = value.value
        done = False
        while not done:
            frac = fractions.Fraction(value).limit_denominator(denom_limit)
            if abs(value - float(frac)) <= tolerance and (frac.numerator <= ctx.param_limit):
                done = True
                value = frac
            else:
                denom_limit *= 10
                if denom_limit > ctx.param_limit:
                    done = True
                    value = None
        return value, tolerance

    def __get_value(self, value, ctx):
        key = (ctx.system, value)
        if key in ctx.let:
            return ctx.let[key]
        else:
            try:
                value = FactorValue(value)
                return value
            except:
                pass
        return None

def parseSystemLine(line): # TODO: THIS SHOULD RETURN NONE IF THE STRIPPED LINE IS NOT A VALID IDENTIFIER
    line = line.strip()
    return ContextCommand('system', line), line


def parseTolerenceLine(line):
    try:
        return ContextCommand('tolerance', float(line))
    except:
        pass
    return None


def parseLetLine(line, system):
    name, _, value = line.partition("=")
    name = name.strip()
    value = value.strip()
    return LetDeclaration(system, name, FactorValue(value))

def parseUnitLine(dimensions, line, message): # TODO: VALIDATE THE DIMENSIONS
    symbol, _, line = line.partition('=')
    symbol = symbol.strip()
    factor, _, line = line.partition('(')
    factor, _, power = factor.partition('**')
    factor = factor.strip()
    power = None if len(power) == 0 else int(power)
    offset = None if len(line) <= 1 else line.rstrip(')').strip()
    return UnitCommand(dimensions, symbol, factor, power, offset, message)

def parseUnitDefinitionFile(filename):
    commands = []
    declarations = []
    current_system = None
    with open(filename) as definition:
        for line in definition.readlines():
            line = line.strip()
            line, _, comment = line.partition('#')
            comment = comment.strip()
            comment = None if len(comment) == 0 else comment
            if len(line) > 0:
                (name, line) = line.split(None, 1)
                new_definition = None
                if name == 'tolerance':
                    new_definition = parseTolerenceLine(line)
                elif name == 'system':
                    new_definition, system = parseSystemLine(line)
                    if not new_definition is None:
                        current_system = system
                elif name == 'let':
                    new_declaration = parseLetLine(line, current_system)
                    if not new_declaration is None:
                        declarations.append(new_declaration)
                else:
                    new_definition = parseUnitLine(name, line, comment)

                if not new_definition is None:
                    commands.append(new_definition)
    return commands, declarations

def processUnitDefinitions(commands, declarations, ctx):
    ctx.let = {}
    for declaration in declarations:
        ctx.let[ (declaration.system, declaration.name) ] = declaration.value
    num_definitions = sum([1 if isinstance(command, UnitCommand) else 0 for command in commands])
    print('{} unit definitions'.format(num_definitions))
    for command in commands:
        command(ctx)
    units = [unit[2] for unit in ctx.units]
    units_text = '\n\n'.join(units)
    print('{} units generated'.format(len(units)))
    return ctx.system, file_template.render(units=units_text, system=ctx.system)

if __name__ == '__main__':
    ctx = UnitsContext()
    commands, declarations = parseUnitDefinitionFile("units.def")
    system, file_text = processUnitDefinitions(commands, declarations, ctx)
    filename = '../Chandra HAL/units_{}.h'.format(system)

    with open(filename, 'w') as file:
        file.write(file_text)

