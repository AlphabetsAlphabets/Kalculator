#ifndef TOKEN_H
#define TOKEN_H

#include <variant>

enum TokenType {
    None,
    Operator,
    Operand,
};

// A token can be two things.
// 1. `TokenType::Operator`.
// 2. `TokenType::Operand`.
//
// One or the other but not both.
class Token {
    private:
        // The precedence of a `Token`. If `Token` is an `Operand` the value will always be 0.
        // Otherwise, the value varies.
        int m_precedence;
        
        TokenType m_type;

        int m_value;

        // Only to be used by non-numeric characters.
        int set_precedence(char c);

        bool is_binary_op(char c);

        bool is_invalid();

    public:
        // Made for compatability. Won't actually be used for processing. 
        // Only used to initialize an empty token that is to be reseated.
        // Or for any other similar process.
        Token();

        // Creates a token.
        Token(char op);

        // Returns `true` if `Token` is `TokenType::Operator`. `false` if it is an `TokenType::Operand`.
        bool is_operator();

        // Returns `true` if self has greater precedence. If `
        bool has_greater_precedence(Token target);

        void update_value(int value);

        // Will return `int` or `char` based on `TokenType`.
        std::variant<int, char> get_value();
};

#endif
