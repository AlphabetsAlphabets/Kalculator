# Kalculator
A calculator made in C++ with operator precedence.

# Limitations
1. The following expressions with parenthesis don't work.
  - `1 + ((2^2)^2)`
  - `((2^2)^2)`
2. Negatives. Such as `- 1 + 2`. The calculator will assume `-` as an `Operand`. This is due to the way things are set.
3. Decimal exponents don't work either.
