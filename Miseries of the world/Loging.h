#pragma once
#include <iostream>
#include <filesystem>
#include <mutex>
#include <chrono>
#include <sstream>

#include <SDL.h>

static std::mutex mutex;

namespace Loging {
	void log(const std::string& message, 
			 const std::filesystem::path& file,
			 const int& line);
}

