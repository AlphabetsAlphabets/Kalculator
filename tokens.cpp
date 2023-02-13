// Normal precedence rules have MULTI and DIVIDE have different precedence.
// But this is just a simple implementation for whole numbers only.

const int MULTI = 2;
const int DIVIDE = 2;
const int ADD = 1;
const int SUB = 1;
const int NUM = 0;


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
        int set_precedence(char c) {
            int precedence = 0;
            switch (c) {
                case '+':
                    precedence = ADD;
                    break;
                case '-':
                    precedence = SUB;
                    break;
                case '*':
                    precedence = MULTI;
                    break;
                case '/':
                    precedence = DIVIDE;
                    break;
            }

            return precedence;
        }

    public:
        // Made for compatability. Won't actually be used for processing. 
	// Only used to initialize an empty token that is to be reseated.
	// Or for any other similar process.
        Token() {}

        // Used only to create an `Operator`
        Token(char op) {
            int precedence = set_precedence(op);
            m_operator = {op, precedence};
        }

        // Used only to create an `Operand`
        Token(int operand) { m_operand = {operand}; }
};

