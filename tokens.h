#ifndef TOKEN_H
#define TOKEN_H

struct Operator {
    char m_op;
    int m_precedence;
};

struct Operand {
    int m_value;
    int m_precedence;
};

class Token {
    private:
        Operator m_operator;
        Operand m_operand;

        int set_precedence(char c);

    public:
        Token();

        Token(char op);

        Token(int operand);
};

#endif
