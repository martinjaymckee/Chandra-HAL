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
${units_overview}

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
        self.default_tolerance = 1e-6
        self.param_limit = int(1e12)
        self.ops = {
            'exact': self.op_exact,
            'offset_decade': self.op_offset_decade,
            'frac': self.op_frac
        }

    @property
    def process_globals(self):
        gl = {k: op for k, op in self.ops.items()}
        gl.update({k: v for (_, k), v in self.let.items()})
        return gl

    def op_frac(self, num, den):
        return fractions.Fraction(num, den)

    def op_offset_decade(self, value):
        try:
            exp = int(value)
            if exp > 0:
                return fractions.Fraction(10**exp, 1)
            elif exp < 0:
                return fractions.Fraction(1, 10**-exp)
            return fractions.Fraction(1, 1)
        except:
            assert False, 'Error: offset_decade() requires integral paramater, received {}'.format(value)

    def op_exact(self, value):
        if isinstance(value, float):
            return fractions.Fraction(value)
        elif isinstance(value, fractions.Fraction):
            return value
        elif isinstance(value, str) or isinstance(value, bytes):
            text = value.strip()
            integral = None
            fractional = ''
            rem = ''
            exp = ''
            if text.find('.') >= 0:
                integral, _, rem = text.partition('.')
                integral = integral.strip()
                fractional, _, exp = rem.partition('e')
                fractional = fractional.strip()
            else:
                integral, _, exp = text.partition('e')
            integral = integral.strip()
            fractional = fractional.strip()
            exp = exp.strip()
            integral_val = 0 if len(integral) == 0 else int(integral)
            fractional_val = 0 if len(fractional) == 0 else int(fractional)
            base_exp_val = 0 if len(exp) == 0 else int(exp)
            exp_frac = len(fractional)
            integral_val *= 10**exp_frac
            fractional_val *= 1 if integral_val >= 0 else -1
            base = fractions.Fraction((integral_val + fractional_val), 1)
            mult = 1
            exp_val = base_exp_val - exp_frac
            if exp_val > 0:
                mult = fractions.Fraction(10**exp_val, 1)
            else:
                mult = fractions.Fraction(1, 10**-exp_val)
            return base * mult
        else:
            assert False, 'Error: function exact() undefined for values of type {}'.format(type(value))

    def process_field(self, field):
        if len(field) > 0:
            gl = self.process_globals
            exec('__result__ = {}'.format(field), gl)
            return gl['__result__']
        return None


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
            if ctx.system not in ctx.names:
                ctx.names[ctx.system] = set()
        if name == 'tolerance':
            ctx.default_tolerance = float(ctx.process_field(value))


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
    def __init__(self, dimensions, symbol, factor, offset, message, absolute=False):
        self.__dimensions = dimensions
        self.__symbol = symbol
        self.__factor = factor
        self.__offset = offset
        self.__absolute = absolute
        self.__message = message

    def __call__(self, ctx):
        factor = ctx.process_field(self.__factor)
        offset = ctx.process_field(self.__offset)
        prefixed, symbol = self.__parse_symbol(self.__symbol, ctx)
        if prefixed:
            self.__prefixed_units(symbol, self.__dimensions, factor, offset, ctx)
        else:
            self.__unit(symbol, self.__dimensions, factor, offset, ctx)

    def __prefixed_units(self, symbol, dimensions, factor, offset, ctx):
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
            ('d', fractions.Fraction(1, 10)),
            ('c', fractions.Fraction(1, 100)),
            ('m', fractions.Fraction(1, 1000)),
            ('u', fractions.Fraction(1, 1000000)),
            ('n', fractions.Fraction(1, 1000000000)),
            ('p', fractions.Fraction(1, 1000000000000)),
            ('f', fractions.Fraction(1, 1000000000000000)),
            ('a', fractions.Fraction(1, 1000000000000000000))
        ]

        for prefix, mult in prefixes:
            prefixed_symbol = prefix + symbol
            self.__unit(prefixed_symbol, dimensions, factor, offset, ctx, mult=mult)

    def __unit(self, symbol, dimensions, factor, offset, ctx, mult=None):
        if symbol not in ctx.names[ctx.system]:
            factor, factor_tol = self.__fractionize(factor, ctx, mult=mult)
            offset, offset_tol = self.__fractionize(offset, ctx)

            added = False
            if (factor is not None):
                offset = fractions.Fraction(0, 1) if offset is None else offset
                max_param = max(factor.numerator, factor.denominator)
                if max_param <= ctx.param_limit and factor != 0:
                    added = True
                    self.__add_unit(ctx, symbol, factor, offset, dimensions)
                    if self.__absolute:
                        self.__add_unit(ctx, symbol, factor, offset, dimensions, absolute=True)
            if not added:
                print("Unable to create {} (factor = {})".format(symbol, factor))
        else:
            assert False, "Attempting to read unit {}".format(symbol)

    def __add_unit(self, ctx, symbol, factor, offset, dimensions, absolute=False):
        main_symbol = symbol + ('_abs' if absolute else '')
        unit_text = unit_template.render(
            symbol=main_symbol,
            rel_symbol=symbol,
            absolute=absolute,
            num=factor.numerator,
            den=factor.denominator,
            factor='approx. {:g}'.format(float(factor)),
            dimensions="dimensions::{}".format(dimensions),
            offset_num=offset.numerator,
            offset_den=offset.denominator
        )
        data = (dimensions, factor, offset)
        ctx.units.append((ctx.system, main_symbol, unit_text, data)) # DO SOMETHING TO ARRANGE THESE....
        ctx.names[ctx.system].add(symbol)

    def __parse_symbol(self, symbol, ctx): # TODO: VALIDATE THE REDUCED SYMBOL AS AN IDENTIFIER
        symbol = symbol.strip()
        if symbol[0] == '*':
            return True, symbol[1:]
        return False, symbol

    def __fractionize(self, value, ctx, mult=None):
        mult = fractions.Fraction(1, 1) if mult is None else mult
        if value is None:
            return None, ctx.default_tolerance
        elif isinstance(value, fractions.Fraction):
            if value.denominator > ctx.param_limit:
                return None, ctx.default_tolerance
            return (mult * value).limit_denominator(ctx.param_limit), 0
        elif isinstance(value, int):
            value = fractions.Fraction(value, 1)
        elif isinstance(value, float):
            value = fractions.Fraction(value)
        else:
            assert False, 'Error: Fractionalize is not defined for values of type = {}'.type(value)
        denom_limit = 10
        done = False
        base_value = fractions.Fraction(value)
        if base_value.numerator == 0:
            return fractions.Fraction(0, 1), 0
        reference_value = mult * base_value
        while not done:
            frac = reference_value.limit_denominator(denom_limit)
            est_err = abs(float(reference_value - frac)) / reference_value
            # print('frac = {}, err_est = {}, tol = {}'.format(frac, est_err, ctx.default_tolerance))
            if est_err <= ctx.default_tolerance and (frac.numerator <= ctx.param_limit):
                done = True
                value = frac
            else:
                denom_limit *= 10
                if denom_limit > ctx.param_limit:
                    done = True
                    value = None
        return value, ctx.default_tolerance


def parseSystemLine(line): # TODO: THIS SHOULD RETURN NONE IF THE STRIPPED LINE IS NOT A VALID IDENTIFIER
    line = line.strip()
    return ContextCommand('system', line), line


def parseTolerenceLine(line):
    try:
        return ContextCommand('tolerance', line)
    except:
        pass
    return None


def parseLetLine(line, system):
    name, _, value = line.partition("=")
    name = name.strip()
    value = value.strip()
    return LetDeclaration(system, name, value)


def parseUnitLine(dimensions, line, message): # TODO: VALIDATE THE DIMENSIONS
    symbol, _, line = line.partition('=')
    symbol = symbol.strip()
    factor, absolute, line = line.partition('@')
    factor = factor.strip()
    offset = line
    return UnitCommand(dimensions, symbol, factor, offset, message, absolute=absolute=='@')


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
                    if new_definition is not None:
                        current_system = system
                elif name == 'let':
                    new_declaration = parseLetLine(line, current_system)
                    if new_declaration is not None:
                        declarations.append(new_declaration)
                else:
                    new_definition = parseUnitLine(name, line, comment)

                if new_definition is not None:
                    commands.append(new_definition)
    return commands, declarations


def processUnitDefinitions(commands, declarations, ctx):
    ctx.let = {}
    for declaration in declarations:
        ctx.let[(declaration.system, declaration.name)] = ctx.process_field(declaration.value)
    num_definitions = sum([1 if isinstance(command, UnitCommand) else 0 for command in commands])
    print('{} unit definitions'.format(num_definitions))
    for command in commands:
        command(ctx)
    units_snippets = [text for system, symbol, text, _ in ctx.units]
    units_data = [(symbol, data) for _, symbol, _, data in ctx.units]
    units_text = '\n\n'.join(units_snippets)
    print('{} units generated'.format(len(units_snippets)))
    units_overview = '//\n// Overview of Units in {} System\n//\n'.format(ctx.system)
    for symbol, (dimensions, factor, offset) in units_data:
        offset_render = '' if offset.numerator == 0 else '@ {:0.2f}'.format(float(offset))
        units_render = '//\t{} {} = {:0.4g} {}\n'.format(dimensions, symbol, float(factor), offset_render)
        units_overview += units_render
    return ctx.system, file_template.render(units=units_text, units_overview=units_overview, system=ctx.system)


if __name__ == '__main__':
    ctx = UnitsContext()
    commands, declarations = parseUnitDefinitionFile("units.def")
    system, file_text = processUnitDefinitions(commands, declarations, ctx)
    # for key, value in ctx.process_globals.items():
    #     print(f'{key}: {value}')
    filename = '../Chandra HAL/units_{}.h'.format(system)

    with open(filename, 'w') as file:
        file.write(file_text)
