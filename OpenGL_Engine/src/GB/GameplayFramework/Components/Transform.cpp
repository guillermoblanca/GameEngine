#include "gbpch.h"
#include "Transform.h"
#include "imgui.h"

namespace GB
{

	Transform::Transform() :Component(),
		pitch(0.0f), yaw(0.0f), roll(0.0f), scale(1.0f)
	{
		position = vector3(0, 0, 0);
	}


	void Transform::Translate(const vector3& pos)
	{
		//todo: find if works
		glm::vec3 dir = pos - position;

		position += dir;
	}

	//void Transform::RotateAround(const vector3& objpos, float radius, float dt)
	//{
	//	objpos.x = position.x + (radius * cos(2 * Mathf::PI() * dt));
	//	objpos.y = position.y + (radius * sin(2 * Mathf::PI() * dt));
	//}

	void GB::Transform::Lerp(const vector3& init, const vector3& des, float dt)
	{
		position = (1 - dt) * init + dt * des;
	}
	void GB::Transform::Lerp0(const vector3& init, const vector3& des, float dt)
	{
		dt = dt > 1 ? 1 : dt < 0 ? 0 : dt;
		position = (1 - dt) * init + dt * des;
	}
	void GB::Transform::SetScale(const vector3& scl)
	{
		scale = scl;
	}

	void Transform::SetScale(float scl)
	{
		scale *= scl;
	}

	void Transform::Rotate(const vector3& rot)
	{
		//rotation = rot;
	}

	glm::mat4 Transform::GetMat4()
	{
		glm::mat4 mat(1.0f);
		mat = glm::translate(mat, position);
		mat = glm::rotate(mat,pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, yaw	, glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, roll, glm::vec3(0.0f, 0.0f, 1.0f));

		mat = glm::scale(mat, scale);
			return mat;
	}


	void Transform::OnUpdate(float DeltaTime)
	{
		//throw std::logic_error("The method or operation is not implemented.");
	}

	void Transform::ImguiRender()
	{
		ImGui::Text("Transform");
		ImGui::SameLine();
		if (ImGui::Button("Reset"))
		{
			position = vector3(0.0f, 0.0f, 0.0f);
			pitch = 0.0f;
			yaw = 0.0f;
			roll = 0.0f;
			scale = vector3(1.0f,1.0f,1.0f);
		}

		ImGui::DragFloat3("Position",(float*)&position, 1.0f);
		{
		ImGui::InputFloat("Pitch", &pitch, 0.1f, 0.01f, 3);
		ImGui::InputFloat("Yaw", &yaw, 0.1f, 0.01f, 3);
		ImGui::InputFloat("Roll", &roll, 0.1f, 0.01f, 3);
		}
		ImGui::DragFloat3("Scale", (float*)&scale, 1);

		
	}

}