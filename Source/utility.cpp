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

#include "utility.h"

namespace youm::utility
{
    NanoTime getNowNanoTime()
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());

        return ns.count();
    }
    string getTime(const char* format)
    {
        std::chrono::time_point<std::chrono::system_clock> now_time = std::chrono::system_clock::now();
        time_t t_time = std::chrono::system_clock::to_time_t(now_time);
        tm tm = *gmtime(&t_time);
        stringstream time_stream;
        time_stream << put_time(&tm, format);
        return time_stream.str();
    }
}
