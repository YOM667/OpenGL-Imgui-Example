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

#include "EngineGUI.h"

void initImgui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImFont* font = io.Fonts->AddFontFromFileTTF("Assets/msyh.ttc", 18.0f, NULL,
        io.Fonts->GetGlyphRangesChineseFull());
}

void createFrame(float x, float y, float width, float height, std::function<void()> const& callback)
{
    ImGui::NewFrame();
    ImGui::SetWindowPos({ x,y });
    ImGui::SetWindowSize({ width,height });
    {
        callback();
    }
    ImGui::End();
    ImGui::Render();
}
