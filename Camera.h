#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
class Camera
{
private:

	glm::vec3 position = { 0.0f, 10.0f, 0.0f };
	glm::vec2 rotation = { 0.0f, 0.0f };

public:
	float sensitivity = 60.0f;
	float speed = 10.0f;
	void FPSMovement(glm::vec2 delta);
	void UpdatePosition(glm::vec3 delta);
	void UpdateRotation(glm::vec2 delta);
	
	glm::vec3 GetPos() {
		return position;
	}

	glm::mat4 GetViewMat();
};

