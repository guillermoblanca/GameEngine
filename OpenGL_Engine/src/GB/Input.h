#pragma once
#include "Core.h"
#include "GB\Math.h"
namespace GB
{
	class GBAPI Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return  s_instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMousePressed(int button) { return s_instance->IsMousePressedImpl(button); }
		inline static  vector2 GetMousePosition() { return s_instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_instance->GetMouseYImpl(); }

		inline static bool IsGamepadConnected(int id) { return s_instance->IsGamepadPresentImpl(id); }
		inline static bool IsGamepadButtonPressed(int id, int buttonId) { return s_instance->IsGamepadButtonPressedImpl(id,buttonId); }
		inline static float GetAxis(int id, int buttonId) { return s_instance->GetAxisImpl(id,buttonId); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMousePressedImpl(int button) = 0;
		virtual vector2 GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		virtual bool IsGamepadPresentImpl(int id) =0;
		virtual bool IsGamepadButtonPressedImpl(int id,int buttonId) = 0;

		virtual float GetAxisImpl(int id, int buttonId) = 0;
	private:
		static Input* s_instance;

	};
}