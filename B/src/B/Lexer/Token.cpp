#include "bpch.h"
#include "Token.h"

namespace B
{
	static std::unordered_map<TokenType, std::string> TokenTypeNameMap
	{
		{ TokenType::None, "<Invalid>" },
		{ TokenType::Int, "Int"},
		{ TokenType::Float, "Float"},
		{ TokenType::Plus, "Plus"},
		{ TokenType::Minus, "Minus"},
		{ TokenType::Multiply, "Mul"},
		{ TokenType::Divide, "Div"},
	};

	bool Token::IsOperand() const
	{
		return Type == TokenType::Int || Type == TokenType::Float;
	}

	bool Token::IsNumber() const
	{
		return Type == TokenType::Int || Type == TokenType::Float;
	}

	bool Token::IsOperator() const
	{
		return Type == TokenType::Plus ||
			Type == TokenType::Minus ||
			Type == TokenType::Multiply ||
			Type == TokenType::Divide;
	}

	bool Token::IsArithmeticOperator() const
	{
		return Type == TokenType::Plus ||
			Type == TokenType::Minus ||
			Type == TokenType::Multiply ||
			Type == TokenType::Divide;
	}

	bool Token::HigherOrderThan(const Token& other) const
	{
		return !((Type == TokenType::Plus && other.Type == TokenType::Multiply) ||
			(Type == TokenType::Plus && other.Type == TokenType::Divide) || 
			(Type == TokenType::Minus && other.Type == TokenType::Multiply) || 
			(Type == TokenType::Minus && other.Type == TokenType::Divide));
	}

}