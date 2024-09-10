#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#endif // _WIN32

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <string>
#include <stack>
#include <chrono>
#include <random>
#include <sstream>
#include <vector>
#include <cmath>
#include <thread>
#include <algorithm>
#include <filesystem>
#include <time.h>

#include "Input.h"
