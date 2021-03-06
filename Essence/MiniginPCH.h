#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>

#include <GL/glew.h>

// TODO: reference additional headers your program requires here
// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

// SDL extension libs 
#pragma comment(lib, "SDL2_image.lib")  
#pragma comment(lib, "SDL2_ttf.lib") 
#pragma comment(lib, "SDL2_mixer.lib")  
#pragma comment(lib, "glew32.lib")

// SDL and OpenGL Includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
//#include <SDL_mixer.h>

#include <windows.h>

#pragma comment(lib, "XInput.lib")
#include <Xinput.h>


#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#pragma warning(pop)