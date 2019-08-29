#include "gbpch.h"
#include "OpenGLRendererAPI.h"
#include "OpenGLTexture2D.h"
#include "glad/glad.h"
namespace GB
{
  
  void OpenGLRendererAPI::SetClearColor(const glm::vec4 & color)
  {
    glClearColor(color.r, color.g, color.b, color.a);
  }
  void OpenGLRendererAPI::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  void OpenGLRendererAPI::AlphaMode(bool active)
  {
    this->m_AlphaMode = active;

    if (active)
    {

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
      glDisable(GL_BLEND);
    }
  }
  void OpenGLRendererAPI::DephtTest(bool active)
  {
    this->m_DephtTest = active;
    if (active)
      glEnable(GL_DEPTH_TEST);
    else
      glDisable(GL_DEPTH_TEST);
  }
  void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
  {
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
  }

}