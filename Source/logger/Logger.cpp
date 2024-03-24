// =========================================================================
// Copyright The YouM, All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// =========================================================================

#include "Logger.h"

void Logger::write_log()
{
}

Logger::Logger(string path = "log", string filename = "devlog") : path(path)
{
	if (!std::filesystem::exists(path))
	{
		std::filesystem::create_directory(path);
	}
	else
	{
		cout << "[Log]: the " + path + "directory had been created" << endl;
	}
	time_point<system_clock> time_point = system_clock::now();
	std::time_t time = system_clock::to_time_t(time_point);
	string current_time = ctime(&time);
	std::ofstream file(path + "\\" + filename + current_time + ".log");
	
	file.close();
}

Logger::~Logger()
{
}

void Logger::log(string message, Level level)
{
	time_point<system_clock> time_point = system_clock::now();
	std::time_t time = system_clock::to_time_t(time_point);
	string current_time = ctime(&time);
	string text = "[" + level + "]" + current_time + " : " + message;
	std::cout << "[]" message << std::endl;
	

string Logger::get_path()
{
	return this->path;
}
