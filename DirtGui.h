#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_vulkan.h"
#include "Camera.h"

/*
* 
* IMGUI is immediate mode, so everything is checked in a loop. there's no callback.
* 
*/ 
class DirtGui
{	
public:
	Camera* camera;
	float fps;
	glm::vec3 pos;

	void ShowWindow();
	void MouseRotation(float dx, float dy);
	glm::vec2 GetMovementInput();
};

