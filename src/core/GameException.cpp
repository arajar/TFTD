#include "pch.h"
#include "GameException.h"

namespace core
{
	GameException::GameException(const std::string& error)
		: std::runtime_error(error)
	{

	}

	GameException::GameException(const char* error)
		: std::runtime_error(error)
	{

	}

	GameException::~GameException() throw()
	{

	}
}