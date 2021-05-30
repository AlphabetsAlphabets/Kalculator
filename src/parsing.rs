#[derive(Debug)]
pub enum TokenType {
    Int,
    Plus,
    Minus,
    Multiply,
    Divide,
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
    pub fn tokenize(self) -> Vec<Token> {
        let mut tokens: Vec<Token> = vec![];

        let x = self.input.chars().map(|ch| {
            match ch {
                '+' => return tokens.push(Token::new(TokenType::Plus, '+')),
                '-' => return tokens.push(Token::new(TokenType::Minus, '-')),
                '/' => return tokens.push(Token::new(TokenType::Divide, '/')),
                '*' => return tokens.push(Token::new(TokenType::Multiply, '*')),
                ' ' => {},
                _ => {
                    if !ch.is_numeric() {
                        return tokens.push(Token::new(TokenType::Eof, 'e'))
                    } else {
                        return tokens.push(Token::new(TokenType::Int, ch))
                    }
                }
            };
        });
        tokens
    }
}
