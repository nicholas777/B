#pragma once

#include "Exceptions/Exception.h"
#include "Parser/SyntaxTree.h"

namespace B
{
	class Interpreter
	{
	public:

		Interpreter() = delete;

		static void Interpret(const std::string& text);
		static void ThrowException(Exception ex);
		static Exception GetException() { return *m_Exception; };

	private:

		enum NumberType
		{
			None = 0,
			Int, Float
		};

		struct NumberValue
		{
			int valuei;
			float valuef;
			NumberType type;

			NumberValue() = default;

			NumberValue(int value)
				: valuei(value), type(NumberType::Int) {};

			NumberValue(float value)
				: valuef(value), type(NumberType::Float) {};
		};

		static Exception* m_Exception;

		static void InterpretSyntaxTree(const SyntaxTree& tree);
		static void InterpretMathTree(const SyntaxTreeNode& tree);

		static NumberValue VisitMathNode(const SyntaxTreeNode& node);

		static NumberValue ComputeArithmetic(TokenType, const NumberValue&, const NumberValue&);
	};
}
