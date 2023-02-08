#include <array>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

const int PAREN = 6;
const int POW = 5;
const int MULTI = 4;
const int DIVIDE = 3;
const int ADD = 2;
const int SUB = 1;

class Token {
    private:
        void set_precedence(char c) {
            switch (c) {
                case '+':
                    m_precedence = ADD;
                    break;
                case '-':
                    m_precedence = SUB;
                    break;
                case '*':
                    m_precedence = MULTI;
                    break;
                case '/':
                    m_precedence = DIVIDE;
                    break;
            }
        }

    public:
        char m_char;
        int m_precedence;

	// `Token` will *always* be an operator. Simply pass in the ascii value of the character
	// and it will be converted to the literal representation via a static cast.
        Token(char c) {
            m_char = static_cast<char>(c);
            set_precedence(c);
        }

        // Returns true if `Token.m_precedence` is greater than `target_op.m_precedence`
        bool compare_precedence(Token target_op) {
            return m_precedence > target_op.m_precedence;
        }

};

class Lexer {
    private:
        std::vector<Token> m_tokens;
        std::vector<char> m_chars;
        std::vector<char>::iterator m_iter;
        std::string m_contents;

        void split_by_char() {
            int length = m_contents.length();
            const char* chars = m_contents.c_str();

            for (int i = 0; i < length; i++) {
                char c = chars[i];
                if (c == ' ') {
                    continue;
                }

                m_chars.push_back(chars[i]);
            }

            m_iter = m_chars.begin();
        }


        int parse_expression(int lhs, int precedence) {
            // 1 + 2 * 3
            // LHS = 1
            bool is_iter_finished = lookahead();
            char next_token = *m_iter; // +
            while (is_binary_op(next_token) && !is_iter_finished) {
                auto op = Token(next_token); 
                is_iter_finished = lookahead();
                int rhs = *m_iter - '0'; // 2
                is_iter_finished = lookahead(); 

                char succeeding_token = *m_iter; // *
                bool is_suceeding_token_op = is_binary_op(succeeding_token); // * is an operator

                auto suceeding_op = Token(succeeding_token);
                // Checks if + or * has more precedence.
                // Should return alse since * is more precedent
                bool is_precedence_greater = op.compare_precedence(suceeding_op.m_precedence);

                while (is_suceeding_token_op && !is_precedence_greater && !is_iter_finished) {
                    is_iter_finished = lookahead();
                    lhs = perform_operation(lhs, op.m_char, rhs);

                    if (is_iter_finished) break;

                    int operand = *m_iter - '0'; // 3
                    rhs = parse_expression(rhs, op.m_precedence + 1);
                }

                lhs = perform_operation(lhs, op.m_char, rhs);
            }

            return lhs;
        }

        int perform_operation(char lhs, char op, char rhs) {
            int res;
            switch (op) {
                case '+':
                    res = lhs + rhs;
                    break;
                case '-':
                    res = lhs - rhs;
                    break;
                case '*':
                    res =  lhs * rhs;
                    break;
                case '/':
                    res =  lhs / rhs;
                    break;
            }

            return res;
        }

        bool is_binary_op(char c) {
            bool res = false;
            switch (c) {
                case '+':
                    res = true;
                    break;
                case '-':
                    res = true;
                    break;
                case '*':
                    res = true;
                    break;
                case '/':
                    res = true;
                    break;
            }

            return res;
        }


        // Moves the iterator forward. Will return true if iterator is at its end.
        bool lookahead() {
            if (*m_iter == *m_chars.end()) {
                return true;
            } else {
                m_iter++;
                return false;
            }
        }

    public:
        Lexer(std::string content) {
            m_contents = content;
            eval();
        }

        void eval() {
            split_by_char();
            // 1 + 2 * 3
            int operand = *m_iter - '0';
            int res = parse_expression(operand, 0);
            std::cout << res << std::endl;
        }
};


int main() {
    // Test
    // https://www.youtube.com/watch?v=jIxsH3E-Hjg
    std::string line = "1 + 4 * 3"; // set a breakpoint here
    auto lexer = Lexer(line);
}
