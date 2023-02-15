#include <string>
#include <vector>

#include "lexer.h"

int main() {
    std::string expr = "2 + 3 * 4 + 5";
    auto lexer = Lexer(expr);
    lexer.eval_expr();
}
