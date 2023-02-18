# Kalculator
A calculator made in C++ with operator precedence.

# Current issues
## The incorrect token is being passed into the second recursive call.
```cpp
while (greater_precedence && !m_iter_finished) {
  inner_expr = Token(eval_expr(next_operand));
  result = perform_operation(next_operand, next_operator, inner_expr);
}
```

## `m_value` isn't being converted.
```cpp
template <>
int Token::get_value<int>() {
    return m_value;
}
```

That was an easy fix. That's because of this.

```cpp
Token::Token(char op) {
    m_type = TokenType::Operand;
    m_precedence = 0;
    m_value = op - '0';

    if (is_binary_op(op)) {
        m_type = TokenType::Operator;
        m_precedence = set_precedence(op);
        m_value = op;
    }
}
```

`m_value = op - '0';` already handled that conversion.
