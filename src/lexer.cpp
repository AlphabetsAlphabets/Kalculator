#include "lexer.h"

Lexer::Lexer(std::string expr) {
    m_iter_finished = false;
    m_iter = m_tokens.begin();
	parse_expr(expr);
}

std::string Lexer::strip_spaces(std::string expr) {
	std::string stripped;
	for (char c : expr) {
		if (c == ' ') continue;

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
	std::string stripped = strip_spaces(expr);
	for (char c : stripped) {
		auto token = create_token(c);
		m_tokens.push_back(token);
	}
}

void Lexer::eval_expr(Token token, int current) {
    Token current_token = lookahead();
    int y = 20;
}

bool Lexer::has_iter_finished() {
    m_iter_finished = m_iter == m_tokens.end();
    return m_iter_finished;
}

Token Lexer::lookahead() {
    if (has_iter_finished()) return Token();

    Token current_token = *m_iter++;

    return current_token;
}
