#pragma once
#include "GB\Core.h"
#include "GB\Render\GraphicContext.h"

struct GLFWwindow;
namespace GB
{
	class OpenGLGraphicContext : public GraphicContext
	{
	public:
		OpenGLGraphicContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}