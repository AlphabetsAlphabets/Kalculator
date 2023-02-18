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

// Curent test: 1 + 2 * 3 + 4
int Lexer::eval_expr(Token current_operand) {
    int result;

    // In the third recursive call `current_operand.m_type` is `TokenType::Operator`
    // So whatever the integer equivalent of the operator will have the same operation 
    // performed in the 2nd recursive call done to it, as well as the result of the
    // previous recursive call.
    //
    // So using the test. The second recursive call is performing 2 * 3. 6 is the result.
    // Then in the 3rd call `current_operand` will be `TokenType::Operator` so `m_value` is 43.
    // So it is 43 * 6.
    //
    // Then on the next call it moves onto 4. I want it to break out the second 2 * 3 is finished.
    // Not sure if this is the right move though since 6 + 4 is still fine. I'll need to think about
    // it. Try 1 + 2 * 3 / 4 + 5.
    if (current_operand.is_invalid()) {
        current_operand = lookahead(); // 1
    }

    Token current_operator = lookahead(); // + 

    bool is_operator = current_operator.is_operator();

    while (is_operator && !m_iter_finished) {
        Token next_operand = lookahead(); // 2
        // This doesn't actually give the operator it gives the value instead
        
        Token next_operator = peek();  // *
        bool is_invalid = next_operand.is_invalid();
        bool greater_precedence = next_operator.has_greater_precedence(current_operator);

        Token inner_expr;
        while (greater_precedence && !m_iter_finished && !is_invalid) {
            int inner_expr = eval_expr(next_operand);
            Token new_token = Token(inner_expr);
            result = perform_operation(next_operand, next_operator, new_token);
        }

        result = perform_operation(current_operand, current_operator, next_operand);
        // Wondering if this has an consequences since the value is just being updated.
        // Should probably change it to something like += instead of just assignment.
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
