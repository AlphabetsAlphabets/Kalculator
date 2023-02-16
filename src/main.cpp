#include <string>
#include <iostream>
#include <vector>

#include "lexer.h"

int main() {
    std::string expr = "2 + 3 * 4 + 5";
    auto lexer = Lexer(expr);
    int result = lexer.eval_expr();
    std::cout << expr << " = " << result << std::endl;
}
