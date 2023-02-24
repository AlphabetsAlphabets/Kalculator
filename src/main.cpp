#include <string>
#include <vector>
#include <iostream>

#include "lexer.h"

int main() {
    std::string expr = "2 * (2 + 5)^3";
    auto lexer = Lexer(expr);
    double result = lexer.eval_expr();
    std::cout << expr << " = " << result << std::endl;
}
