#include <array>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cctype>

const int MULTI = 2;
const int DIVIDE = 2;
const int ADD = 1;
const int SUB = 1;
const int NUM = 0;
const int NAN = -1;

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
                default:
                    if (!std::isdigit(c)) {
                        m_precedence = NAN;
                    } else {
                        m_precedence = NUM;
                        m_operand = c - '0';
                    }
            }
        }

    public:
        char m_op;
        bool m_is_op;
        int m_precedence;

        int m_operand;

        Token() {}

        Token(char c, bool is_op) {
            m_is_op = is_op;
            m_op = c;
            set_precedence(c);
        }

        Token(int operand) {
            m_is_op = false;
            m_precedence = NUM;
            m_operand = operand;
        }

        // Returns true if `m_precedence` is greater than or equal 
        // `target_op.m_precedence`
        bool compare_precedence(Token& target_op) {
            return m_precedence > target_op.m_precedence;
        }
};

class Lexer {
    private:
        std::vector<Token> m_tokens;
        std::vector<char> m_chars;
        std::vector<char>::iterator m_iter;
        std::string m_contents;
        bool m_is_iter_finished;

        // Gets all the characters from the string, and remove any whitespace
        void split_by_char() {
            int length = m_contents.length();
            const char* chars = m_contents.c_str();

            for (int i = 0; i < length; i++) {
                char c = chars[i];
                if (c == ' ' || c == '\0') {
                    continue;
                }

                m_chars.push_back(chars[i]);
            }

            m_iter = m_chars.begin();
        }


        Token parse_expression(Token lhs) {
            Token op = lookahead();
            bool greater_eq_precedence = op.compare_precedence(lhs);

            while (op.m_is_op && greater_eq_precedence && !m_is_iter_finished) {
                Token rhs = lookahead();

                Token succeeding_op = lookahead();
                bool greater_precedence_than_op = succeeding_op.compare_precedence(op);

                while (succeeding_op.m_is_op && greater_precedence_than_op && !m_is_iter_finished) {
                    lookahead();

                    lhs = perform_operation(lhs, op, rhs);

                    if (m_is_iter_finished) break;

                    rhs = parse_expression(rhs);
                    // lookahead(); // The return isn't used, so the 3rd op is completely ignored
                }

                lhs = perform_operation(lhs, op, rhs);
                op = succeeding_op;
            }

            return lhs;
        }

        Token perform_operation(Token lhs, Token op, Token rhs) {
            int result;
            int v1 = lhs.m_operand;
            int v2 = rhs.m_operand;

            switch (op.m_op) {
                case '+':
                    result = v1 + v2;
                    break;
                case '-':
                    result = v1 - v2;
                    break;
                case '*':
                    result =  v1 * v2;
                    break;
                case '/':
                    result =  v1 / v2;
                    break;
            }

            // Result is calculated properly but token is NAN.
            auto resultant_token = Token(result);
            return resultant_token;
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
        Token lookahead() {
            // Should only trigger once which is at the start 
            if (m_iter == m_chars.begin()) {
                auto token = Token(*m_iter++, false);
                return token;
            } 

            char next = *m_iter++;
            Token token;

            bool is_op = is_binary_op(next);

            if (is_op) {
                token = Token(next, is_op);
            } else {
                token = Token(next);
            }

            m_is_iter_finished = m_iter == m_chars.end();

            return token;
        }

    public:
        Lexer(std::string content) {
            m_contents = content;
            eval();
        }

        void eval() {
            split_by_char();
            // This assumes that the first character is always going to be a positive number.
            Token lhs = lookahead();
            lhs = parse_expression(lhs);
            std::cout << lhs.m_operand << std::endl;
        }
};


int main() {
    /* std::string line; */
    /* std::cout << "Expression: "; */
    /* getline(std::cin, line); */
    std::string line = "1 + 2 * 3";
    auto lexer = Lexer(line);
}
