#include "bpch.h"
#include "Parser.h"
#include "B/Interpreter.h"

namespace B
{

	SyntaxTree Parser::Parse()
	{
		SyntaxTree tree;

		if (m_Tokens[m_Index].IsArithmeticOperator())
		{
			Interpreter::ThrowException(Exception(ExceptionType::InvalidSyntaxException, "Invalid syntax", 0));
			return tree;
		}

		while (m_Index < m_Tokens.size())
		{
			Token& token = m_Tokens[m_Index];

			if (token.IsOperand() || token.Type == TokenType::LeftParen)
			{
				tree.Root = ProcessOperatorToken();
			}

			Advance();
		}

		return tree;
	}

	void Parser::Advance(int i)
	{
		m_Index += i;
	}

	SyntaxTreeNode Parser::ProcessOperatorToken()
	{
		SyntaxTreeNode result;
		Token& operand = m_Tokens[m_Index];

		// Whether there is an operator or right parenthesis
		if (m_Tokens.size() > m_Index + 1 )
		{
			if (m_Tokens[m_Index + 1].Type == TokenType::RightParen)
				return operand;

			Token& op = m_Tokens[m_Index + 1];

			if (m_Tokens[m_Index].Type == TokenType::LeftParen)
			{
				Advance();

				if (!(m_Tokens.size() > m_Index + 1))
				{
					Interpreter::ThrowException(Exception(ExceptionType::InvalidSyntaxException, "Incomplete statement", 0));
					return SyntaxTreeNode();
				}

				else if (!m_Tokens[m_Index].IsNumber())
				{
					Interpreter::ThrowException(Exception(ExceptionType::InvalidSyntaxException, "Invalid parenthesis statement", 0));
					return SyntaxTreeNode();
				}

				else if (m_Tokens[m_Index + 1].Type == TokenType::RightParen)
				{
					Advance(1);
					return SyntaxTreeNode(m_Tokens[m_Index - 1]);
				}

				else if (m_Tokens[m_Index + 1].IsOperator())
				{
					SyntaxTreeNode parenNode = ProcessOperatorToken();

					if (m_Tokens[m_Index + 1].Type != TokenType::RightParen)
					{
						Interpreter::ThrowException(Exception(ExceptionType::InvalidSyntaxException, "Incomplete statement", 0));
						return SyntaxTreeNode();
					}

					Advance(2);

					return parenNode;
				}

				else
				{
					Interpreter::ThrowException(Exception(ExceptionType::InvalidSyntaxException, "Incomplete statement", 0));
					return SyntaxTreeNode();
				}
			}

			// Whether there is a second operand
			if (m_Tokens.size() > m_Index + 2)
			{
				Advance(2);

				if (m_Tokens[m_Index].Type == TokenType::LeftParen)
				{
					result.token = op;
					result.children.push_back(operand);
					result.children.push_back(ProcessOperatorToken());
					return result;
				}

				SyntaxTreeNode node = ProcessOperatorToken();

				result.token = op;

				if (node.token.IsOperand())
				{
					result.children.push_back(operand);
					result.children.push_back(node);
					return result;
				}

				if (node.token.HigherOrderThan(result.token))
				{
					result.children.push_back(operand);
					result.children.push_back(node);
					return result;
				}
				else
				{
					SyntaxTreeNode& child1 = node.children[0]; // 2 
					SyntaxTreeNode& child2 = node.children[1]; // 4
					node.children.clear();

					result.children.push_back(operand);
					result.children.push_back(child1);

					node.children.push_back(result);
					node.children.push_back(child2);

					return node;
				}
			}
			else
			{
				Interpreter::ThrowException(Exception(ExceptionType::InvalidSyntaxException, "Incomplete statement", 0));
				return SyntaxTreeNode();
			}
		}
		else
		{
			return operand;
		}
	}

}
