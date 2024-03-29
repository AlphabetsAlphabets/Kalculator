#include "token.h"

const int PAREN = 4;
const int EXPO = 3;
const int MULTI = 2;
const int DIVIDE = 2;
const int ADD = 1;
const int SUB = 1;
const int NUM = 0;

Token::Token() {
    m_type = TokenType::None;
    m_precedence = 0;
}

Token::Token(std::string value) {
    m_type = TokenType::Operand;
    m_precedence = 0;
    try {
        m_value = std::stod(value);
    } catch (const std::invalid_argument) {
        char op = value[0];
        m_type = TokenType::Operator;
        m_value = (double) op;
        m_precedence = set_precedence(op);
    }
}

Token::Token(char op) {
    m_type = TokenType::Operator;
    m_value = (double) op;
    m_precedence = set_precedence(op);
}

Token::Token(double num) {
    m_type = TokenType::Operator;
    m_value = num;
    m_precedence = 0;
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
        case '^':
            precedence = EXPO;
            break;
        case ')':
            precedence = PAREN;
            break;
        case '(':
            precedence = PAREN;
            break;
    }

    return precedence;
}


bool Token::is_invalid() {
    return m_type == TokenType::None;
}

bool Token::is_operator() {
    return m_type == TokenType::Operator && !is_invalid();
}

bool Token::has_greater_precedence(Token target) {
    return m_precedence > target.m_precedence;
}

// TODO: Will need to test these two functions
template <>
char Token::get_value<char>() {
    return (char) m_value;
}

template <>
double Token::get_value<double>() {
    return m_value;
}

void Token::update_value(double value) {
    m_value = value;
}
