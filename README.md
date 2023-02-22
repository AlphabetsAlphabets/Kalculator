# Kalculator
A calculator made in C++ with operator precedence.

# Limitations
1. There must be spaces between each operator.

- `1 + 2 * 3`
- `3 / 3 * 200`

Without it, the calculator will just break.
- `1+2*3` - Will break the whole thing.

The reason is because tokens are separated via whitespace. A better way would be to go through the whole thing character by character and peeking ahead like you're supposed to.

2. Parenthesis are not supported. Not yet anyways.
