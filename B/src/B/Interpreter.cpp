#include "bpch.h"
#include "Interpreter.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

namespace B
{
	Exception* Interpreter::m_Exception = nullptr;

	void Interpreter::Interpret(const std::string& text)
	{
		Lexer lexer{ text };
		std::vector<Token> tokens = lexer.Lex();
		if (m_Exception)
		{
			std::cout << m_Exception->ToString() << std::endl;
			return;
		}

		Parser parser{ tokens };
		SyntaxTree tree = parser.Parse();
		if (m_Exception)
		{
			std::cout << m_Exception->ToString() << std::endl;
			return;
		}

		InterpretSyntaxTree(tree);

		lexer.FreeTokens(tokens);
	}

	void Interpreter::ThrowException(Exception ex)
	{
		m_Exception = new Exception;
		*m_Exception = ex;
	}

	void Interpreter::InterpretSyntaxTree(const SyntaxTree& tree)
	{
		if (tree.Root.token.IsOperator() || tree.Root.token.IsOperand())
		{
			NumberValue v = VisitMathNode(tree.Root);

			switch (v.type)
			{
				case NumberType::Int:
					std::cout << v.valuei << std::endl;
					break;
				case NumberType::Float:
					std::cout << v.valuef << std::endl;
					break;
			}
		}
	}

	Interpreter::NumberValue Interpreter::VisitMathNode(const SyntaxTreeNode& node)
	{
		if (node.token.IsNumber())
		{
			switch (node.token.Type)
			{
				case TokenType::Int:
					return NumberValue(*(int*)node.token.Data);
				case TokenType::Float:
					return NumberValue(*(float*)node.token.Data);
			}
		}

		int result = 0;
		NumberValue operands[2];

		for (int i = 0; i < node.children.size(); i++)
		{
			const SyntaxTreeNode& child = node.children[i];
			operands[i] = VisitMathNode(child);
		}

		// There will always be two operands in an arithmetic operation
		if (node.token.IsArithmeticOperator())
		{
			return ComputeArithmetic(node.token.Type, operands[0], operands[1]);
		}

		return 0;
	}

	Interpreter::NumberValue Interpreter::ComputeArithmetic(TokenType op, const NumberValue& operand1, const NumberValue& operand2)
	{
		switch (op)
		{
			case TokenType::Plus:
				return (operand1.type == NumberType::Int ? operand1.valuei : operand1.valuef) + (operand2.type == NumberType::Int ? operand2.valuei : operand2.valuef);
			case TokenType::Minus:
				return (operand1.type == NumberType::Int ? operand1.valuei : operand1.valuef) - (operand2.type == NumberType::Int ? operand2.valuei : operand2.valuef);
			case TokenType::Multiply:
				return (operand1.type == NumberType::Int ? operand1.valuei : operand1.valuef) * (operand2.type == NumberType::Int ? operand2.valuei : operand2.valuef);
			case TokenType::Divide:
				return (operand1.type == NumberType::Int ? operand1.valuei : operand1.valuef) / (operand2.type == NumberType::Int ? operand2.valuei : operand2.valuef);
		}

		return 0;
	}

}
