#include "gbpch.h"
#include "OrbitalCamera.h"

vector2 GB::OrbitalCamera::GetCameraDirection()
{
	direction = GB::Input::GetMousePosition();
	vector2 diff = lastDirection - direction;
	lastDirection = direction;
	return diff;
}

void GB::OrbitalCamera::Tick()
{
	lastTick += Time::DeltaTime();

	Window* window = &Application::Get().GetWindow();

	float x = Input::GetMouseX() / (float)window->GetWidth() * 16;
	float y = Input::GetMouseY() / (float)window->GetHeight() * 16;

	


}

void GB::OrbitalCamera::InputMode()
{
	if (Input::IsMousePressed(1))
	{
		vector2 diff = GetCameraDirection();
		vector3 direction = vector3
		(
			diff.x * speed,
			-diff.y * speed,
			0.0f
		);

		//Translate(direction);
	}

	if (Input::IsMousePressed(2))
	{
		float y = GetCameraDirection().y;
	//	Translate(vector3(0.0f, 0.0f, y * speed * 2));

	}

	if (Input::IsKeyPressed(GB_KEY_LEFT_ALT) && Input::IsMousePressed(0))
	{
		vector2 direction = GetCameraDirection();
	//	Rotate(direction.x, vector3(0.f, 1.0f, 0.0f));
	//	Rotate(direction.y, vector3(1.f, 0.0f, 0.0f));
	}

}

