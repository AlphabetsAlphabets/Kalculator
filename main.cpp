#include <iostream>
#include <vector>
#include <string>

const char DIVIDE = '/';
const char ADD = '+';
const char SUB = '-';
const char MULTI = '*';

class Lexer {
    private:
        std::vector<char> m_chars;
        std::vector<char> m_tokens;
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
                char token;
                if (c == DIVIDE) {
                    token = DIVIDE;
                } else if (c == ADD) {
                    token = ADD;
                } else if (c == MULTI) {
                    token = MULTI;
                } else {
                    token = SUB;
                }

                m_tokens.push_back(token);
            }
        }

    public:
        Lexer(std::string content) {
            m_contents = content;
            tokenize();
        }
};

void match(const char& c) {
    if (c == DIVIDE) {
    }

}

int main() {
    std::string line = "1 + 2 / 5 * 3";
    auto lexer = Lexer(line);
}
