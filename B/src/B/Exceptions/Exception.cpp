#include "bpch.h"
#include "Exception.h"

namespace B
{
	static std::unordered_map<ExceptionType, std::string> ExceptionNameMap =
	{
		{ ExceptionType::None, "Invalid Exception" },
		{ ExceptionType::InvalidTokenException, "InvalidTokenException"},
		{ ExceptionType::InvalidSyntaxException, "InvalidSyntaxException"}
	};

	std::string Exception::ToString()
	{
		std::string str = ExceptionNameMap[m_Type] + " at line " + std::to_string(m_Line) + ": " + m_Message;
		return str;
	}
}
