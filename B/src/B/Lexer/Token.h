#pragma once

namespace B
{

#define TOKEN_PLUS Token(TokenType::Plus)
#define TOKEN_MINUS Token(TokenType::Minus)
#define TOKEN_MUL Token(TokenType::Multiply)
#define TOKEN_DIV Token(TokenType::Divide)
#define TOKEN_LEFT_PAREN Token(TokenType::LeftParen)
#define TOKEN_RIGHT_PAREN Token(TokenType::RightParen)

	enum class TokenType
	{
		None = 0,
		Int, Float, 
		Plus, Minus, Divide, Multiply, LeftParen, RightParen
	};

	struct Token
	{
		TokenType Type = TokenType::None;
		void* Data = nullptr;

		Token() = default;
		Token(TokenType type, void* data = nullptr)
			: Type(type), Data(data) {};

		bool IsOperand() const;
		bool IsNumber() const;
		bool IsOperator() const;
		bool IsArithmeticOperator() const;

		bool HigherOrderThan(const Token& other) const;

	};
}
