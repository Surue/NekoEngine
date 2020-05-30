#include <stats.h>

#include <imgui.h>
#include <sstream>
#include <engine/engine.h>

namespace neko::tool {

void StatsTool::DrawImGui()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::Begin("Neko Window");

	std::ostringstream oss;
	oss << "App FPS: " << 1.0f / BasicEngine::GetInstance()->GetDeltaTime() << '\n'
		<< '\n';
	ImGui::Text("%s", oss.str().c_str());
	ImGui::End();
}
} //namespace nok::tool
