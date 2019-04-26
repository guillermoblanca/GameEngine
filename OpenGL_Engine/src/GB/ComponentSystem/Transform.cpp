#include "gbpch.h"
#include "Transform.h"

GB::Transform::Transform()
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

void GB::Transform::Translate(glm::vec3 pos)
{
	//todo: find if works
	auto dir = pos - position;

	position += dir;
}

void GB::Transform::Lerp(glm::vec3 pos, float dt)
{
	dt = dt > 1 ? 1 : dt < 0 ? 0 : dt;
	position = (1 - dt)*position + dt * pos;
}

void GB::Transform::SetScale(glm::vec3 scl)
{
	scale = scl;
}

void GB::Transform::Rotate(glm::vec3 rot)
{
	rotation = rot;
}

glm::mat4 GB::Transform::GetMat4()
{
	glm::mat4 mat(1.0f);
	mat = glm::translate(mat, position);
	mat = glm::rotate(mat, rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));
	mat = glm::rotate(mat, rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, rotation[2], glm::vec3(0.0f, 0.0f, 1.0f));

	mat = glm::scale(mat, scale);

	return mat;
}
