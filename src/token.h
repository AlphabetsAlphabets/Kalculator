#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <cmath>
#include <stdexcept>

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

        double m_value;

        // Only to be used by non-numeric characters.
        int set_precedence(char c);

    public:
        // Made for compatability. Won't actually be used for processing. 
        // Only used to initialize an empty token that is to be reseated.
        // Or for any other similar process.
        Token();

        // Creates a token from a string.
        Token(std::string num);

        // Creats a token from a `char`. Used only by `Operator`.
        Token(char op);
        
        // Creats a token from a `double`. Used only by `Operand`.
        Token(double num);

        // Returns `true` if `Token` is `TokenType::Operator`. `false` if it is an `TokenType::Operand`.
        bool is_operator();

        // Returns `true` if the instance has greater precedence.
        bool has_greater_precedence(Token target);

        // Returns `true` if `m_type` is `TokenType::None`
        bool is_invalid();

        // Only to be used when `m_type == TokenType::Operand`
        void update_value(double value);

        // Will return `int` or `char` based on `TokenType`.
        template <typename T>
        T get_value();
};

#endif
