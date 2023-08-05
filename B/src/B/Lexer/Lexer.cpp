#include "bpch.h"
#include "Lexer.h"
#include "B/Interpreter.h"

namespace B
{
	std::vector<Token> Lexer::Lex()
	{
		std::vector<Token> tokens{};

		while (m_Index < m_Text.size())
		{
			char c = m_Text[m_Index];

			if (c == ' ')
			{
				Advance();
				continue;
			}

			if (isdigit(c))
			{
				tokens.push_back(GetDigitToken());
				continue;
			}
			else
			{
				switch (c)
				{
					case '+':
						tokens.push_back(TOKEN_PLUS);
						break;
					case '-':
						tokens.push_back(TOKEN_MINUS);
						break;
					case '*':
						tokens.push_back(TOKEN_MUL);
						break;
					case '/':
						tokens.push_back(TOKEN_DIV);
						break;
					case '(':
						tokens.push_back(TOKEN_LEFT_PAREN);
						break;
					case ')':
						tokens.push_back(TOKEN_RIGHT_PAREN);
						break;
					default:
						Interpreter::ThrowException(Exception(ExceptionType::InvalidTokenException, "Invalid character", 0));
						return std::vector<Token>();
				}
			}

			Advance();
		}

		return tokens;
	}

	void Lexer::FreeTokens(const std::vector<Token>& tokens)
	{
		for (auto& token : tokens)
		{
			switch (token.Type)
			{
				case TokenType::Float:
					delete (float*)token.Data;
					break;
				case TokenType::Int:
					delete (int*)token.Data;
					break;
			}
		}
	}

	void Lexer::Advance()
	{
		m_Index++;
	}

	Token Lexer::GetDigitToken()
	{
		uint32_t index = m_Index;
		char* data = new char[64];
		memset(data, 0, sizeof(data));

		bool dotFound = false;

		while (isdigit(m_Text[m_Index]) || m_Text[m_Index] == '.')
		{
			if (m_Text[m_Index] == '.' && dotFound == false)
				dotFound = true;
			else if (m_Text[m_Index] == '.' && dotFound == true)
				break;
			
			data[m_Index - index] = m_Text[m_Index];

			Advance();
		}

		if (!dotFound)
		{
			int* result = new int;
			*result = atoi(data);
			return Token(TokenType::Int, result);
		}
		else
		{
			float* result = new float;
			*result = atof(data);
			return Token(TokenType::Float, result);
		}
	}
}