#include <string>
#include <iostream>
#include <vector>

#include "lexer.h"

int main() {
    std::string expr = "1+2.2^3 - 20";
    auto lexer = Lexer(expr);
    double result = lexer.eval_expr();
    std::cout << expr << " = " << result << std::endl;
}
