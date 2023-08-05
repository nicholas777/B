#pragma once

#include "B/Lexer/Token.h"

namespace B
{
	struct SyntaxTreeNode
	{
		Token token;
		std::vector<SyntaxTreeNode> children;

		SyntaxTreeNode() = default;
		SyntaxTreeNode(const Token& tok)
			: token(tok) {};
	};

	struct SyntaxTree
	{
		SyntaxTreeNode Root;
	};
}