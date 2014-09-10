#pragma once

// Useful macros for development, will show a TODO message when compiling
#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define TODO(msg) __pragma( message (__FILE__ "[" STRING(__LINE__) "] --- TODO: " msg ))

///////////////////////////////////////////////////////////////////////////////

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

#include "GL/glew.h"

#include "sfml/graphics.hpp"
#include "sfml/OpenGL.hpp"
#include "sfml/System.hpp"
#include "sfml/Window.hpp"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"

#include "util/Identifier.h"
#include "util/Singleton.h"
#include "util/Delegate.h"
#include "GameException.h"
#include "resources/ContentManager.h"
#include "filesystem/FileSystem.h"
#include "resources/IResource.h"
#include "util/Tweener.h"
#include "util/Util.h"

#include "lights/Light.h"

#include "ecs/ecs.h"

#include "imgui.h"

#include "resources/Image.h"

#include "Engine.h"
#include "Events.h"
