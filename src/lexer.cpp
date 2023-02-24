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

bool Lexer::is_binary_op(char op) {
    bool is_operator = false;
    switch (op) {
        case '+':
            is_operator = true;
            break;
        case '-':
            is_operator = true;
            break;
        case '*':
            is_operator = true;
            break;
        case '/':
            is_operator = true;
        case '^': 
            is_operator = true;
            break;
        case '(':
            is_operator = true;
            break;
        case ')':
            is_operator = true;
            break;
    }

    return is_operator;
}

void Lexer::parse_expr(std::string expr) {
    std::string stripped = strip_spaces(expr);
    std::string num;
    for (char c : stripped) {
        if (std::isdigit(c)) {
            num += c;
        } else if (c == '.') {
            num += c;
        } else if (is_binary_op(c)) {
            Token op = Token(c);
            
            // The order the tokens are being pushed into the vector matters.
            // That's because in `eval_expr` the expected order is that the
            // odd elements in the vector are `Operand`s and the even are `Operator`s.
            
            if (!num.empty()) {
                Token value = Token(num);
                m_tokens.push_back(value);
                num.clear();
            }

            m_tokens.push_back(op);
        }  
    }
}

double Lexer::eval_expr(Token current_operand) {
    if (current_operand.is_invalid()) {
        current_operand = lookahead();
    }

    Token current_operator = lookahead();

    bool is_operator = current_operator.is_operator();

    double result;
    while (is_operator && !m_iter_finished) {
        bool is_open_paren = current_operator.get_value<char>() == ')';
        if (is_open_paren) {
            current_operator = lookahead();
        }

        Token next_operand = lookahead(); 

        // Found the starting paren, entering it.
        if (next_operand.get_value<char>() == '(') {
            next_operand = eval_expr(lookahead());
        }

        Token next_operator = peek(); 

        bool is_invalid = next_operand.is_invalid() && next_operator.is_invalid();

        bool greater_precedence = next_operator.has_greater_precedence(current_operator);

        // Found the ending paren, skipping it.
        if (next_operator.get_value<char>() == ')') {
            greater_precedence = false;
        }

        Token inner_expr;
        while (greater_precedence && !m_iter_finished && !is_invalid) {
            std::string inner_expr = std::to_string(eval_expr(next_operand));
            Token new_token = Token(inner_expr);
            result = perform_operation(current_operand, current_operator, new_token);
            current_operand.update_value(result);
        } 

        // This is completely skipped if expr is (x + y)^z because
        // is_invalud is true
        if (!is_invalid){
            result = perform_operation(current_operand, current_operator, next_operand);
            current_operand.update_value(result);
            current_operator = lookahead();
        }

    }

    return current_operand.get_value<double>();
}

bool Lexer::has_iter_finished() {
    m_iter_finished = m_iter == m_tokens.end();
    return m_iter_finished;
}

double Lexer::perform_operation(Token lhs, Token op, Token rhs) {
    double v1 = lhs.get_value<double>();
    double v2 = rhs.get_value<double>();
    double res;

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
        case '^':
            res = std::pow(v1, v2);
            break;
    }

    return res;
}

Token Lexer::lookahead() {
    if (has_iter_finished()) return Token();

    return *m_iter++;
}

Token Lexer::peek() {
    Token next = *m_iter++;
    --m_iter;
    return next;
}
