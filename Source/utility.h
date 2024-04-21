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
#include <chrono>
#include <ctime>
#include <iostream>
#include <cmath>
#include <chrono>

#include <sstream>
#include <iomanip>

typedef long long NanoTime;

#define NANOSECOND 1000000000L
#define FRAMERATE 0.001

using namespace std;

namespace youm::utility
{
    NanoTime getNowNanoTime();
    string getTime(const char* format);
}
