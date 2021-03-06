#pragma once

// C++ STL
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <list>
#include <filesystem>

// FMOD:
#pragma warning( push )
#pragma warning( disable: 26812 ) // Unscoped enum.
#include <FMOD/fmod.hpp>
#pragma warning( pop )

// Windows:
#define NOMINMAX
#include <windows.h>
#undef CreateDirectory
