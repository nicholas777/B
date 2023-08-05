#pragma once

#include "B/Lexer/Token.h"
#include "SyntaxTree.h"

namespace B
{
	class Parser
	{
	public:

		Parser() = default;
		Parser(const std::vector<Token>& tokens)
			: m_Tokens(tokens) {};

		SyntaxTree Parse();

	private:

		std::vector<Token> m_Tokens;
		uint32_t m_Index = 0;

		void Advance(int i = 1);

		SyntaxTreeNode ProcessOperatorToken();

	};
}