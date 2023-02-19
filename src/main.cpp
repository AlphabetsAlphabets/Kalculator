#include <string>
#include <iostream>
#include <vector>

#include "lexer.h"

int main() {
    std::string expr = "3 / 3 + 1 * 9 * 9 + 500"; // 582, this doens't work because it interprets 500 and individual digits lmao
    auto lexer = Lexer(expr);
    int result = lexer.eval_expr();
    std::cout << expr << " = " << result << std::endl;
}
