#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <iterator>

#include "token.h"

// The lexer is used to read an expression and only an expression.
// An expression will not contain any characters other than whole numbers
// and operators. This might change in the future.
class Lexer {
    private:
        // Each `Token` in the vector is stored in the order received through `expr`
        // when `expr` is passed in the constructor.
        std::vector<Token> m_tokens;

        // An iterator of `Token`
        std::vector<Token>::iterator m_iter;

        // `true` if iterator of `m_tokens` is finished.
        bool m_iter_finished;

        // Strips `expr` of all spaces
        std::string strip_spaces(std::string expr);

        // Creates tokens and populates `m_tokens`
        void parse_expr(std::string expr);

        bool has_iter_finished();

        // Returns the current token in the iterator then advances it.
        // Will return immediately if iterator is already at its end.
        Token lookahead();

        // Returns the next token without advancing the iterator.
        Token peek();

        int perform_operation(Token lhs, Token op, Token rhs);

    public:
        // Evaluates the expression.
        // `current_token` will always be an `Operand` never an `Operator`.
        int eval_expr(Token current_operand=Token());
        Lexer(std::string expr);
};

#endif
