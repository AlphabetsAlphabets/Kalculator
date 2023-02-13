#ifndef TOKEN_H
#define TOKEN_H

struct Operator {
	char m_op;
	int m_precedence;
};

struct Operand {
	int m_value;
	// This is only for compatability, will always be 0.
	int m_precedence;
};

// A token can be two things.
// 1. An `Operator`.
// 2. An `Operand`.
//
// One or the other but not both.
class Token {
	private:
		Operator m_operator;
		Operand m_operand;

		// Only to be used by non-numeric characters.
		int set_precedence(char c);

	public:
		// Made for compatability. Won't actually be used for processing. 
		// Only used to initialize an empty token that is to be reseated.
		// Or for any other similar process.
		Token();

		// Used only to create an `Operator`
		Token(char op);

		// Used only to create an `Operand`
		Token(int operand);
};

#endif
