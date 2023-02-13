#include <string>
#include <vector>
#include "tokens.h"

// The lexer is used to read an expression and only an expression.
// An expression will not contain any characters other than whole numbers
// and operators. This might change in the future.
class Lexer {
    private:
        // Each `Token` in the vector is stored in the order received through `expr`
        // when `expr` is passed in the constructor.
        std::vector<Token> m_tokens;

        std::string strip_whitespace(std::string expr) {
            std::string stripped;
            for (char c : expr) {
                if (c == ' ') {
                    continue;
                }

                stripped += c;
            }

            return stripped;
        }

        Token create_token(char c) {
            bool is_digit = std::isdigit((int) c);
            auto token = Token();
            if (is_digit) {
                token = Token(c - '0');
            } else {
                token = Token(c);
            }

            return token;
        }

        void parse_expr(std::string expr) {
            std::string stripped = strip_whitespace(expr);
            for (char c : stripped) {
                auto token = create_token(c);
                m_tokens.push_back(token);
            }
        }

	// Evalutes `m_tokens` and produces an output.
	void evaluate_expr() {
	}

    public:
        Lexer(std::string expr) {
            // Creates tokens and populates `m_tokens`
            parse_expr(expr);
        }
};
