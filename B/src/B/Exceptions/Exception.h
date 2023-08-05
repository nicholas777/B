#pragma once

namespace B
{
	enum class ExceptionType
	{
		None = 0,
		InvalidTokenException,
		InvalidSyntaxException
	};

	class Exception
	{
	public:
		Exception() = default;
		Exception(ExceptionType type, const std::string& msg, uint32_t line)
			: m_Type(type), m_Message(msg), m_Line(line) {};

		~Exception() = default;

		const std::string& ToString();
	private:
		ExceptionType m_Type = ExceptionType::None;
		std::string m_Message;
		uint32_t m_Line = 0;
	};
}
