#include "token.h"

const int MULTI = 2;
const int DIVIDE = 2;
const int ADD = 1;
const int SUB = 1;
const int NUM = 0;

Token::Token() {
    m_type = TokenType::None;
    m_precedence = 0;
}

Token::Token(char op) {
    m_type = TokenType::Operand;
    m_precedence = 0;

    if (is_binary_op(op)) {
        m_type = TokenType::Operator;
        m_precedence = set_precedence(op);
    }
}

int Token::set_precedence(char c) {
    int precedence = 0;
    switch (c) {
        case '+':
            precedence = ADD;
            break;
        case '-':
            precedence = SUB;
            break;
        case '*':
            precedence = MULTI;
            break;
        case '/':
            precedence = DIVIDE;
            break;
    }

    return precedence;
}

bool is_binary_op(char c) {
    bool is_operator = false;
    switch (c) {
        case '+':
            is_operator = true;
            break;
        case '-':
            is_operator = true;
            break;
        case '*':
            is_operator = true;
            break;
        case '/':
            is_operator = true;
            break;
    }

    return is_operator;
}

bool Token::is_invalid() {
    return m_type == TokenType::None;
}

bool Token::is_operator() {
    return m_type == TokenType::Operator && !is_invalid();
}

std::variant<int, char> Token::get_value() {
    if (is_operator()) {
        return m_value;
    } else {
        return m_value - '0';
    }
}
