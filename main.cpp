#include <iostream>
#include <vector>
#include <string>

const int PAREN = 6;
const int POW = 5;
const int MULTI = 4;
const int DIVIDE = 3;
const int ADD = 2;
const int SUB = 1;

class Lexer {
    private:
        std::vector<char> m_chars;
        std::vector<int> m_operators;
        std::vector<int> m_operands;
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
        }

        void tokenize() {
            split_by_char();
            int size = std::size(m_chars);
            for (int i = 0; i < size; i++) {
                auto c = m_chars[i];
                int level = 1;
                if (c == '(' || c == ')') {
                    level = PAREN;
                } else if (c == '^') {
                    level = POW;
                } else if (c == '*') {
                    level = MULTI;
                } else if (c == '/') {
                    level = DIVIDE;
                } else if (c == '+') {
                    level = ADD;
                } else if (c == '-') {
                    level = SUB;
                } else {
                    m_operands.push_back(c + '0');
                }

                m_operators.push_back(level);
            }
        }

    public:
        Lexer(std::string content) {
            m_contents = content;
            tokenize();
        }

        void print_tokens() {
            int size = std::size(m_operators);
            for (int i = 0; i < size; i++) {
                std::cout << m_operators[i];
            }

            std::cout << std::endl;
        }

        void calc() {

        }
};

void match(const char& c) {
    if (c == DIVIDE) {
    }

}

int main() {
    std::string line = "1 + 2 / 5 * 3";
    auto lexer = Lexer(line);
    lexer.print_tokens();
}
