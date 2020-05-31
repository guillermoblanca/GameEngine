#pragma once
#include "Event.h"

namespace GB
{
	class GamePadStatesEvent :public Event
	{
	public:

		GamePadStatesEvent(bool isConnected,const char* name) : m_isConnected(isConnected),m_gamepadName(name) {}

		bool IsConnected() { return m_isConnected; }
		const char* GetGamepadName() const { return m_gamepadName; }
		EVENT_CLASS_TYPE(GamepadState)

			EVENT_CLASS_CATEGORY(EventCategoryGamepad | EventCategoryInput)
			std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Gamepad "<< m_gamepadName <<": " << (m_isConnected  ? "Connected" : "Disconnected");
			return ss.str();
		}
	private:
		bool m_isConnected;
		const char* m_gamepadName;
	};
}