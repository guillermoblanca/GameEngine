#include "gbpch.h"
#include "WindowsInput.h"

#include <GLFW\glfw3.h>
#include "GB\Application.h"
namespace GB
{

	Input* Input::s_instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMousePressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state =glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	vector2 WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return vector2(xpos,ypos);
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto v = GetMousePositionImpl();
		return v.x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto v = GetMousePositionImpl();
		return v.y;
	}

}
