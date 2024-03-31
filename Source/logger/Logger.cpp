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

using namespace youm::utility;
const char* Logger::levels[LEVEL_COUNT] = {
	"DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};
Logger* Logger::log_instance = nullptr;
Logger::Logger()
{
}
Logger::~Logger()
{
	close();
}
Logger* Logger::instance()
{
	if (log_instance == nullptr)
	{
		log_instance = new Logger();
	}
	return log_instance;
}

void Logger::open(const string& file_name)
{
	const char* file_path = "./log/";
	if (!filesystem::exists(file_path)) 
	{
		filesystem::create_directory(file_path);
	}
	this->local_file = file_path + file_name;
	out_stream.open(local_file, ios::app);
	if (out_stream.fail())
	{
		throw runtime_error("open the file: " + local_file + " error");
	}
}

void Logger::close()
{
	out_stream.close();
}

void Logger::log(Level level, const char* file, int line, const char* message, ...)
{
	time_point<system_clock> now_time = system_clock::now();
	time_t t_time = system_clock::to_time_t(now_time);
	tm tm = *gmtime(&t_time);
	stringstream time_stream;
	time_stream << put_time(&tm, "%Y-%m-%d %H:%M:%S");
	string time = time_stream.str();
	const char* format = "%s %s [%s %d]: ";
	int size = snprintf(nullptr, 0, format, time.c_str(), levels[(int)level], file, line);
	if(size > 0)
	{
		char* buffer = new char[size + 1];
		snprintf(buffer, size + 1, format, time.c_str(), levels[(int)level], file, line);
		buffer[size] = 0;
		cout << buffer;
		out_stream << buffer;
		delete[] buffer;
	}
	va_list arg_ptr;
	va_start(arg_ptr, message);
	size = vsnprintf(nullptr,0,message,arg_ptr);
	va_end(arg_ptr);
	if (size > 0)
	{
		char* content = new char[size + 1];
		va_start(arg_ptr, message);
		size = vsnprintf(content, size + 1, message, arg_ptr);
		va_end(arg_ptr);
		cout << content << endl;
		out_stream << content;
	}
	out_stream << "\n";
	out_stream.flush();
}
