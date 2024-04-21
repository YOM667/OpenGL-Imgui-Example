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

// The Game Engine lanucher
// useage: 1. Create GameEngine object
//         2. Use GameEngine's render() method, while your program will block.
//            Your program maybe lanuch successfully
//         3. you need use GameEngine's method shutdown() after method render()
// tips  : You're better off not using the 'new' form of creating GameEngine pointers
//         that may cause memory overflow when you lanuche the program multiple times
#include "GameEngine.h"

int main(int argc, char* argv[])
{
    youm::Maple::GameEngine engine(youm::Maple::GameEngine::Mode::DEV,{0.1,0.5,0.4,1.0});
    engine.run();
    return 0;
}