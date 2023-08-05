#include "bpch.h"
#include "Exception.h"

namespace B
{
	static std::unordered_map<ExceptionType, std::string> ExceptionNameMap =
	{
		{ ExceptionType::None, "Invalid Exception" },
		{ ExceptionType::InvalidTokenException, "InvalidTokenException"}
	};

	const std::string& Exception::ToString()
	{
		return ExceptionNameMap[m_Type] + " at line " + std::to_string(m_Line) + ": " + m_Message;
	}
}
