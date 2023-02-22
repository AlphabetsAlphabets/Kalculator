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
    std::string expr = "1.1 + 0.5";
    auto lexer = Lexer(expr);
    double result = lexer.eval_expr();
    std::cout << expr << " = " << result << std::endl;
}
