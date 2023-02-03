#include <iostream>
#include <vector>
#include <string>

const char DIVIDE = '/';
const char ADD = '+';
const char SUB = '-';
const char MULTI = '*';

void match(const char& c) {
    if (c == DIVIDE) {
    }

}

int main() {
    std::string input = "";
    getline(std::cin, input);

    // Number of chars without the termination character
    int size = input.size();
    // Characters with the termination character
    const char* characters = input.c_str();

    for (int i = 0; i < size; i++) {
        char character = characters[i];
        std::cout << character << std::endl;
    }
}
