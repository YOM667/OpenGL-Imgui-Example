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