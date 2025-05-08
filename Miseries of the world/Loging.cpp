#include "Loging.h"

void Loging::log(const std::string& message,
				 const std::filesystem::path& file, 
				 const int& line)
{
	std::lock_guard<std::mutex> guard(mutex);

	auto time = std::chrono::system_clock::now();
	auto nowTime = std::chrono::system_clock::to_time_t(time);

	std::tm vTm;
	localtime_s(&vTm, &nowTime);
	
	std::ostringstream timeStamp;
	std::cout << std::put_time(&vTm, "%Y-%m-%d %H:%M:%S");
	
	std::cerr << "[ERROR][" << timeStamp.str() << ']'<<"[SDL_ERROR: "<<SDL_GetError()<<']';
	if (!file.empty())
	{
		std::cerr << '[' << file.string() << ']';
		if (line > 0) 
			std::cerr << "[LINE: " << line << ']';
	}
	std::cout << "[MESSAGE]" << '[' << message << ']' << '\n';
}
