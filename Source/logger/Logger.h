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

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <chrono>
#include <iomanip>

#include <stdarg.h>


using namespace std;
using namespace std::chrono;
const unsigned int LEVEL_COUNT = 5;

namespace youm
{
	namespace utility
	{
#define debug(message, ...) \
		Logger::instance()->log(Level::LEVEL_DEBUG,__FILE__,__LINE__, message, __VA_ARGS__)

#define info(message, ...) \
		Logger::instance()->log(Level::LEVEL_INFO,__FILE__,__LINE__, message, __VA_ARGS__)

#define error(message, ...) \
		Logger::instance()->log(Level::LEVEL_ERROR,__FILE__,__LINE__, message, __VA_ARGS__)

#define warning(message, ...) \
		Logger::instance()->log(Level::LEVEL_WARNING,__FILE__,__LINE__, message, __VA_ARGS__)

#define fatal(message, ...) \
		Logger::instance()->log(Level::LEVEL_FATAL,__FILE__,__LINE__, message, __VA_ARGS__)


		enum class Level
		{
			LEVEL_DEBUG, LEVEL_INFO, LEVEL_WARN, LEVEL_ERROR, LEVEL_FATAL
		};

		class Logger
		{
		public:

			Logger();
			~Logger();
			static Logger* instance();
			void open(const string& file_name);
			void close();
			void log(Level level, const char* file, int line, const char* message, ...);
		private:

			string local_file;
			ofstream out_stream;
			static const char* levels[LEVEL_COUNT];
			static Logger* log_instance;
		};

	}
}
