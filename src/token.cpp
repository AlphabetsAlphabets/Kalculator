#include "token.h"

const int MULTI = 2;
const int DIVIDE = 2;
const int ADD = 1;
const int SUB = 1;
const int NUM = 0;

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

Token::Token() {
    m_is_invalid = true;
}

Token::Token(char op) {
    m_is_invalid = false;
    m_precedence = set_precedence(op);

    m_operator = {op}; 
}

Token::Token(int operand) { 
    m_is_invalid = false;
    m_precedence = -2;

    m_operand = { operand }; 
}

bool Token::is_operator() {
    return m_precedence >= 1;
}

bool Token::has_greater_precedence(Token target) {
    return m_precedence > target.m_precedence || target.m_is_invalid;
}
