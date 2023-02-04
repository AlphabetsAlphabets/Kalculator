#include <string>
#include <array>
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

class Lexer {
    private:
        std::vector<char> m_chars;
        std::vector<char> m_postfix;
        std::vector<char> m_operators;
        std::vector<char> m_operands;
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

        void tokenize(const char target) {
            split_by_char();
            int size = std::size(m_chars);
            // (1 + 2) * 3 = 1 2 3 + *
            // 2 * 3 - 1 = 2 3 1 * -
            // 3 * (1 - 2) = 3 1 2 - *
            
            if (target == '(') {
                auto it = std::find(m_chars.begin(), m_chars.end(), target);
                int index = std::distance(m_chars.begin(), it);
                std::vector<char> remainder(m_chars.begin() + index, m_chars.end());
            }
        }

    public:
        Lexer(std::string content) {
            m_contents = content;
            tokenize('(');
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
    // https://www.youtube.com/watch?v=jIxsH3E-Hjg
    std::string line = "3 * (1 - 2)";
    auto lexer = Lexer(line);
    lexer.print_tokens();
}
