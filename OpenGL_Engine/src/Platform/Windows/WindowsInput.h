#pragma once
#include "GB\Input.h"
namespace GB
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMousePressedImpl(int button) override;
		virtual vector2 GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

		virtual bool IsGamepadPresentImpl(int id)override;
		virtual bool IsGamepadButtonPressedImpl(int id, int buttonId) override;

		virtual float GetAxisImpl(int id, int butt)override;
	};
}