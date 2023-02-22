#include <string>
#include <iostream>
#include <vector>

#include "lexer.h"

void print_tokens(std::vector<std::string> tokens) {
    for (auto token: tokens) {
        std::cout << "'" << token << "'" << std::endl;
    }
}

int main() {
    std::string expr = "1 + 2 * 3";
    auto lexer = Lexer(expr);
    int result = lexer.eval_expr();
    std::cout << expr << " = " << result << std::endl;
}
