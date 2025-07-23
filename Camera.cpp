#include "Camera.h"

void Camera::FPSMovement(glm::vec2 delta)
{
	float rx = glm::radians(rotation.x);
	float ry = glm::radians(rotation.x - 90.0f);
	float rz = glm::radians(rotation.y);

	float fz = glm::cos(rz);
	float z = glm::sin(rz) * -delta.y;

	float y1 = glm::cos(rx) * -delta.y * fz;
	float x1 = glm::sin(rx) * delta.y * fz;

	float y2 = glm::cos(ry) * delta.x;
	float x2 = glm::sin(ry) * -delta.x;

	glm::vec3 d =  {x1 + x2, z, y1 + y2};

	UpdatePosition(d * speed);
}

void Camera::UpdatePosition(glm::vec3 delta)
{
	position += delta;
}

void Camera::UpdateRotation(glm::vec2 delta)
{
	rotation += delta * sensitivity;
	rotation.y = rotation.y > 90.0f ? 90.0f : rotation.y;
	rotation.y = rotation.y < -90.0f ? -90.0f : rotation.y;

	rotation.x += rotation.x > 360.0f ? -360 : 0.0f;
	rotation.x += rotation.x < 0.0f ? 360 : 0.0f;
}

glm::mat4 Camera::GetViewMat()
{
	glm::mat4 rotM = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(1.0f, 0.0f, 0.0f));
	rotM = glm::rotate(rotM, glm::radians(rotation.x), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 transM = glm::translate(glm::mat4(1.0f), -position);
	return rotM * transM;
}
