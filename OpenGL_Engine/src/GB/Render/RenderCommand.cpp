#include "gbpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace GB
{
  RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}