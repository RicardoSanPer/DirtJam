#pragma once

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_vulkan.h"

/*
* 
* IMGUI is immediate mode, so everything is checked in a loop. there's no callback.
* 
*/ 
class DirtGui
{
private:
	float myFloat = 0;
public:
	void ShowWindow();
};

