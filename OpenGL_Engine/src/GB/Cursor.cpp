#include "gbpch.h"
#include "Cursor.h"
#include "GLFW/glfw3.h"

void GB::Cursor::SetCursorPosition(float xPos, float yPos)
{
	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	glfwSetCursorPos(window, xPos, yPos);
}

void GB::Cursor::SetVisibleCursor(bool activate)
{
	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	glfwSetInputMode(window, GLFW_CURSOR, activate ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}
