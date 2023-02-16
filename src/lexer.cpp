#include "lexer.h"

Lexer::Lexer(std::string expr) {
    parse_expr(expr);

    m_iter_finished = false;
    m_iter = m_tokens.begin();
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

int Lexer::eval_expr(Token current_operand) {
    current_operand = lookahead();
    Token current_operator = lookahead();

    bool is_operator = current_operator.is_operator();
    bool greater_precedence = current_operator.has_greater_precedence(current_operand);

    while (is_operator && greater_precedence && !m_iter_finished) {
        Token next_operand = lookahead();
        Token succeeding_operator = lookahead();
        greater_precedence = succeeding_operator.has_greater_precedence(current_operator);

        while (greater_precedence && !m_iter_finished) {
            eval_expr(next_operand);
        }

        int result = perform_operation(current_operand, current_operator, next_operand);
        current_operand.m_operand.m_value = result;
    }

    return current_operand.m_operand.m_value;
}

bool Lexer::has_iter_finished() {
    m_iter_finished = m_iter == m_tokens.end();
    return m_iter_finished;
}

int Lexer::perform_operation(Token lhs, Token op, Token rhs) {
    int v1 = lhs.m_operand.m_value;
    int v2 = rhs.m_operand.m_value;
    int res;

    // Should implement some sort of getter
    switch (op.m_operator.m_op) {
        case '+':
            res = v1 + v2;
            break;
        case '-':
            res = v1 - v2;
            break;
        case '*':
            res =  v1 * v2;
            break;
        case '/':
            res =  v1 / v2;
            break;
    }

    return res;
}

Token Lexer::lookahead() {
    if (has_iter_finished()) return Token();

    return *m_iter++;
}
