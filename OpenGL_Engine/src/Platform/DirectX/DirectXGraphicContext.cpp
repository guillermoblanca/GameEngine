#include "GB\Core.h"
#include "GB\Render\GraphicContext.h"

struct GLFWwindow;
namespace GB
{
  class DirectXGraphicContext : public GraphicContext
  {
  public:
    DirectXGraphicContext(GLFWwindow* windowHandle);
    virtual void Init() override;
    virtual void SwapBuffers() override;

  private:
    GLFWwindow* m_WindowHandle;
  };
}