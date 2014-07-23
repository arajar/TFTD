#pragma once

// Useful macros for development, will show a TODO message when compiling
#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define TODO(msg) __pragma( message (__FILE__ "[" STRING(__LINE__) "] --- TODO: " msg ))

#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <iostream>
#include <map>
#include <ctime>
#include <functional>

#include "sdl.h"
#include "sdl_image.h"
#include "sdl_ttf.h"

typedef unsigned int uint;
typedef std::pair<int, int> vec2i;
typedef std::pair<float, float> vec2f;

#include "core/Singleton.h"
#include "core/GameException.h"
#include "core/ContentManager.h"
#include "core/resources/IResource.h"
#include "core/util/Timer.h"
#include "core/util/Tweener.h"

// Useful operators for std::pair
template <typename T1, typename T2>
std::pair<T1, T2> operator+(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2)
{
	return std::pair<T1, T2>(p1.first + p2.first, p1.second + p2.second);
}

template <typename T1, typename T2>
std::pair<T1, T2> operator-(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2)
{
	return std::pair<T1, T2>(p1.first - p2.first, p1.second - p2.second);
}

template <typename T1, typename T2>
std::pair<T1, T2> operator*(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2)
{
	return std::pair<T1, T2>(p1.first * p2.first, p1.second * p2.second);
}

template <typename T1, typename T2, typename T3>
std::pair<T1, T2> operator*(const std::pair<T1, T2>& p1, T3 p2)
{
	return std::pair<T1, T2>(static_cast<T1>(static_cast<T3>(p1.first) * p2), static_cast<T2>(static_cast<T3>(p1.second) * p2));
}
