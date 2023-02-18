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
	return Token(c);
}

void Lexer::parse_expr(std::string expr) {
	std::string stripped = strip_spaces(expr);
	for (char c : stripped) {
		auto token = create_token(c);
		m_tokens.push_back(token);
	}
}

// Curent test: 2 + 3 * 4 + 5
// Currently there are two main problems.
// 1. `succeeding_operator` is never `*`.
// 2. The iterator is advanced too quickly. Sometimes I need to peek and sometimes I need to advance. I have no idea how to create a check to determine which should come first.
int Lexer::eval_expr(Token current_operand) {
    int result;

    if (!current_operand.is_operator()) {
        current_operand = lookahead();
    }

    Token current_operator = lookahead();

    bool is_operator = current_operator.is_operator();

    while (is_operator && !m_iter_finished) {
        Token next_operand = lookahead();
        // This doesn't actually give the operator it gives the value instead
        Token succeeding_operator = peek(); 
        bool greater_precedence = succeeding_operator.has_greater_precedence(current_operator);

        Token inner_expr;
        while (greater_precedence && !m_iter_finished) {
            inner_expr = Token(eval_expr(next_operand));
            result = perform_operation(current_operand, succeeding_operator, inner_expr);
        }

        result = perform_operation(current_operand, current_operator, next_operand);

        current_operand.update_value(result);
    }

    return current_operand.get_value<int>();
}

bool Lexer::has_iter_finished() {
    m_iter_finished = m_iter == m_tokens.end();
    return m_iter_finished;
}

int Lexer::perform_operation(Token lhs, Token op, Token rhs) {
    int v1 = lhs.get_value<int>();
    int v2 = rhs.get_value<int>();
    int res;

    switch (op.get_value<char>()) {
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

Token Lexer::peek() {
    // NOTE: I don't think a check is needed. This is most definitely not true.
    Token next = *m_iter++;
    --m_iter;
    return next;
}
