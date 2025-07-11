#include "DirtGui.h"

void DirtGui::ShowWindow()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("My Window");
	//inputs return true when the value changes bewteen frames
	//Use public flags to query in the vulkan app to change values only if they're changed?
	ImGui::SliderFloat("My Float", &rotation, 0.0f, 360.0f);
	
	ImGui::End();
}
