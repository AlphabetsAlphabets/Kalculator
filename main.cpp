#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "tokens.h"
#include "lexer.h"


int main() { 
    std::string expr = "2 + 3 * 4 + 5"; 
    auto lexer = Lexer(expr);
}
