#ifndef TOKEN_H
#define TOKEN_H

struct Operator {
    char m_op;
};

struct Operand {
    int m_value;
};

// A token can be two things.
// 1. An `Operator`.
// 2. An `Operand`.
//
// One or the other but not both.
class Token {
    private:
        // This is only used when `Token::Token()` is called.
        bool m_is_invalid;
        // Only to be used by non-numeric characters.
        int set_precedence(char c);

    public:
        int m_precedence;
        Operator m_operator;
        Operand m_operand;

        // Made for compatability. Won't actually be used for processing. 
        // Only used to initialize an empty token that is to be reseated.
        // Or for any other similar process.
        Token();

        // Used only to create an `Operator`
        Token(char op);

        // Used only to create an `Operand`
        Token(int operand);

        // Returns `true` if `Token` is `Operator`. `false if it is an `Operand`.
        bool is_operator();

        // Returns `true` if self has greater precedence. If `
        bool has_greater_precedence(Token target);
};

#endif
