#include <string>
#include <vector>

const int MULTI = 2;
const int DIVIDE = 2;
const int ADD = 1;
const int SUB = 1;
const int NUM = 0;
const int NAN = -1;

struct Operator {
    char m_op;
    int m_precedence;
};

struct Operand {
    int m_value;
    // This is only for compatability, will always be 0.
    int m_precedence;
};

// A token can be two things.
// 1. An operator
// 2. An operand
class Token {
    private:
        Operator m_operator;
        Operand m_operand;

        // Only to be used by non-numeric characters.
        int set_precedence(char c) {
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

    public:
        // Default constructor. Fallback to default member initialisation.
        Token() {}

        // Used only to create an `Operator`
        Token(char op) {
            int precedence = set_precedence(op);
            m_operator = {op, precedence};
        }

        // Used only to create an `Operand`
        Token(int operand) { m_operand = {operand}; }
};

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
            Token token;
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

    public:
        Lexer(std::string expr) {
            // Creates tokens and populated `m_tokens`
            parse_expr(expr);
        }
};

int main() { std::string expr = "2 + 3 * 4 + 5"; }
