#[derive(Debug)]
pub enum TokenType {
    Int,
    Plus,
    Minus,
    Multiply,
    Divide,
    Percent,
    Eof,
    // LPAREN,
    // RPAREN,
    // POWER,
    // ILLEGAL,
}

#[derive(Debug)]
pub struct Token {
    token_type: TokenType,
    literal: char,
}

impl Token {
    pub fn new(token_type: TokenType, literal: char) -> Self {
        Token {
            token_type,
            literal,
        }
    }
}

/// Reponsible for taking apart the input string.
pub struct Lexer {
    input: String,
}

impl Lexer {
    pub fn new(s: &str) -> Self {
        Lexer {
            input: s.to_string()
        }
    }

    // TODO: Get tokenizer working.
    // https://createlang.rs/
    // https://fenga.medium.com/how-to-build-a-calculator-bf558e6bd8eb
    // https://www.twilio.com/blog/abstract-syntax-trees
    pub fn tokenize(self) -> Vec<Token> {
        let mut tokens: Vec<Token> = vec![];

        // Before it was with a map(), but it needs to be used
        // This is just easier with a for loop.
        for ch in self.input.chars() {
            match ch {
                '+' => tokens.push(Token::new(TokenType::Plus, '+')),
                '-' => tokens.push(Token::new(TokenType::Minus, '-')),
                '/' => tokens.push(Token::new(TokenType::Divide, '/')),
                '*' => tokens.push(Token::new(TokenType::Multiply, '*')),
                '%' => tokens.push(Token::new(TokenType::Percent, '%')),
                ' ' => {},
                _ => {
                    if !ch.is_numeric() {
                        tokens.push(Token::new(TokenType::Eof, 'e'))
                    } else {
                        tokens.push(Token::new(TokenType::Int, ch))
                    }
                }
            };
        }
        tokens
    }
}
