#include <string>
#include <vector>

#include "lexer.h"
#include "token.h"

std::string Lexer::strip_whitespace(std::string expr) {
	std::string stripped;
	for (char c : expr) {
		if (c == ' ') {
			continue;
		}

		stripped += c;
	}

	return stripped;
}

Token Lexer::create_token(char c) {
	bool is_digit = std::isdigit((int) c);
	Token token;
	if (is_digit) {
		token = Token(c - '0');
	} else {
		token = Token(c);
	}

	return token;
}

void Lexer::parse_expr(std::string expr) {
	std::string stripped = strip_whitespace(expr);
	for (char c : stripped) {
		auto token = create_token(c);
		m_tokens.push_back(token);
	}
}

Lexer::Lexer(std::string expr) {
	// Creates tokens and populated `m_tokens`
	parse_expr(expr);
}
