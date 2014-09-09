#pragma once

#include <stdexcept>

namespace core
{
	using std::runtime_error;

	class GameException : public runtime_error
	{
	public:
		explicit GameException(const std::string& error);
		explicit GameException(const char* error);

		virtual ~GameException() throw();
	};
}