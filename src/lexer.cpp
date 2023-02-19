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

void Lexer::parse_expr(std::string expr) {
	std::string stripped = strip_spaces(expr);
	for (char c : stripped) {
		auto token = Token(c);
		m_tokens.push_back(token);
	}
}

// Curent test: 3 / 3 + 1 * 9 * 9 + 500 = 582
int Lexer::eval_expr(Token current_operand) {
    if (current_operand.is_invalid()) {
        current_operand = lookahead(); // 1
    }

    Token current_operator = lookahead(); // + 

    bool is_operator = current_operator.is_operator();

    int result;
    while (is_operator && !m_iter_finished) {
        Token next_operand = lookahead(); 
        Token next_operator = peek();  // *
        bool is_invalid = next_operand.is_invalid() && next_operator.is_invalid();
        bool greater_precedence = next_operator.has_greater_precedence(current_operator);

        Token inner_expr;
        while (greater_precedence && !m_iter_finished && !is_invalid) {
            int inner_expr = eval_expr(next_operand);
            Token new_token = Token(inner_expr);
            result = perform_operation(current_operand, current_operator, new_token);
            current_operand.update_value(result);
        } 

        if (!is_invalid && !greater_precedence) {
            result = perform_operation(current_operand, current_operator, next_operand);
            current_operand.update_value(result);
            current_operator = lookahead();
        }
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
