#pragma once

#include "Token.h"

namespace B
{
	class Lexer
	{
	public:
		Lexer() = default;
		Lexer(const std::string& text)
			: m_Text(text) {};

		std::vector<Token> Lex();

		void FreeTokens(const std::vector<Token>& tokens);
	private:

		std::string m_Text;
		uint32_t m_Index = 0;

		void Advance();
		Token GetDigitToken();

	};
}