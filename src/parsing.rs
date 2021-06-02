#[derive(Debug)]
pub enum TokenType {
    Int,
    Plus,
    Minus,
    Multiply,
    Divide,
    Percent,
    Eof,
    Lparen,
    Rparen,
    Power,
    Decimal,
    // Illegal,
}

pub struct Expression {
    left: String,
    right: String,
}

impl Expression {
    pub fn new(left: String, right: String) -> Self {
        Expression { left, right }
    }
}

/// token_type: Enum TokenType
/// operator: char
/// value: number
/// left: String
/// right: String
#[derive(Debug)]
pub struct Token {
    token_type: TokenType,
    operator: char,
    left: String,
    right: String,
}

impl Token {
    /// TokenType: Guarenteed
    /// Operator: Not guarenteed
    /// Left: Not guarenteed
    /// Right: not guarenteed
    pub fn new(token_type: TokenType, operator: char, left: String, right: String) -> Self {
        Token {
            token_type,
            operator,
            left,
            right,
        }
    }

    pub fn int(self) -> String {
        let value = self.right;
        match value.parse::<usize>() {
            Ok(_) => {}
            Err(_) => panic!("{} is not a number", value),
        };
        format!("{}", value)
    }

    pub fn prefix(self) -> String {
        let token = self.token_type;
        let operator = self.operator;
        let value = self.right;

        format!("{}{}", operator, value)
    }

    pub fn infix(self) -> String {
        let left = self.left;
        let right = self.right;
        let operator = self.operator;

        format!("{}{}{}", left, operator, right)
    }
}

/// Reponsible for taking apart the input string.
pub struct Lexer {
    input: String,
}

impl Lexer {
    pub fn new(s: &str) -> Self {
        Lexer {
            input: s.to_string(),
        }
    }

    // TODO: Get tokenizer working.
    // https://createlang.rs/
    // https://fenga.medium.com/how-to-build-a-calculator-bf558e6bd8eb
    // https://www.twilio.com/blog/abstract-syntax-trees
    pub fn tokenize(self) -> Vec<Token> {
        let mut tokens: Vec<Token> = vec![];

        for (c, ch) in self.input.chars().enumerate() {
            let left = {
                if c == 0 {
                    "".to_string()
                } else {
                    let left = &self.input[c - 1..c];
                    left.to_owned()
                }
            };

            let right = {
                if c == self.input.len() - 1{
                    "".to_string()
                } else {
                    let right = &self.input[c + 1..c + 2];
                    right.to_owned()
                }
            };

            match ch {
                '+' => tokens.push(Token::new(TokenType::Plus, '+', left, right)),
                '-' => tokens.push(Token::new(TokenType::Minus, '-', left, right)),
                '/' => tokens.push(Token::new(TokenType::Divide, '/', left, right)),
                '*' => tokens.push(Token::new(TokenType::Multiply, '*', left, right)),
                '%' => tokens.push(Token::new(TokenType::Percent, '%', left, right)),
                '(' => tokens.push(Token::new(TokenType::Lparen, ch, left, right)),
                ')' => tokens.push(Token::new(TokenType::Rparen, ch, left, right)),
                '^' => tokens.push(Token::new(TokenType::Power, ch, left, right)),
                '.' => tokens.push(Token::new(TokenType::Decimal, ch, left, right)),
                _ => {
                    if !ch.is_numeric() {
                        tokens.push(Token::new(TokenType::Eof, 'e', left, right))
                    } else {
                        tokens.push(Token::new(TokenType::Int, ch, left, right))
                    }
                }
            };
        }
        tokens
    }
}
