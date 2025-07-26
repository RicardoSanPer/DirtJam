#include "DirtGui.h"

void DirtGui::ShowWindow()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("My Window");
	ImGui::Text("%0.2f ms (%.2f fps)", (1.0f/fps)*1000.0f, fps);
	ImGui::Text("x: %.2f\ny: %.2f\nz: %.2f", pos.x, pos.y, pos.z);
	//inputs return true when the value changes bewteen frames
	//Use public flags to query in the vulkan app to change values only if they're changed?
	/*ImGui::SliderFloat("My Float", &rotationX, 0.0f, 360.0f);
	ImGui::SliderFloat("My Float 2", &rotationY, -90.0f, 90.0f);*/
	ImGui::End();
}

void DirtGui::MouseRotation(float dx, float dy)
{
	camera->UpdateRotation({ dx, dy });
}

glm::vec2 DirtGui::GetMovementInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	glm::vec2 delta = { 0,0 };

	if (state[SDL_SCANCODE_W])
	{
		delta.y += 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		delta.y -= 1;
	}
	if (state[SDL_SCANCODE_A])
	{
		delta.x -= 1;
	}
	if (state[SDL_SCANCODE_D])
	{
		delta.x += 1;
	}

	return delta;
}
