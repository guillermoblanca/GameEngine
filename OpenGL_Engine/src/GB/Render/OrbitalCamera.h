#pragma once
#include "GB.h"

namespace GB
{
	class OrbitalCamera : Camera
	{

	private:

		OrbitalCamera()
		{
			target = vector3(3.0f, 0.0f, 0.0f);
			direction = vector2(0.0f, 0.0f);
			lastDirection = vector2(0.0f, 0.0f);

			lastTick = 0.0f;
			distance = 10.f;
			speed = 0.01f;
		}

		vector3 target;
		vector2 direction; //mouse direction
		vector2 lastDirection;// mouse predirection
		float distance;
		float lastTick;
		float speed;

		vector2 GetCameraDirection();

		void Tick();

	protected:
		virtual void InputMode();
	};
}
