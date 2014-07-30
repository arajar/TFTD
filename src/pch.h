#pragma once

// Useful macros for development, will show a TODO message when compiling
#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define TODO(msg) __pragma( message (__FILE__ "[" STRING(__LINE__) "] --- TODO: " msg ))

#include <typeinfo>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <ctime>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "sdl.h"
#include "sdl_image.h"
#include "sdl_ttf.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"

#include "core/Singleton.h"
#include "core/GameException.h"
#include "core/ContentManager.h"
#include "core/resources/IResource.h"
#include "core/util/Timer.h"
#include "core/util/Tweener.h"

#include "core/ecs/ecs.h"