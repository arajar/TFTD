#pragma once

#include <stdexcept>

namespace core
{
	using std::runtime_error;

	class GameException : public runtime_error
	{
	public:
		GameException(const std::string& error);

		GameException(const char* error);

		virtual ~GameException() throw();
	};
}