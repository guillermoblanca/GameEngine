#pragma once

#pragma region Includes
#include "GB\Core.h"

#include "Material.h"
#include "Buffer.h"
/*
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
*/


#include "GB\ComponentSystem\Transform.h"
#pragma endregion


namespace GB
{
 
  struct RenderData
  {
    RenderData(float& data, unsigned int indices, std::string path);
    std::shared_ptr<VertexBuffer> m_buffer;
    std::shared_ptr<IndexBuffer> m_indexbuffer;
    std::shared_ptr<Material*> m_mat;
  };


  class GBAPI IRender
  {
  public:
    virtual void Render(Material& material, int mode = 4) = 0;
  };


  class GBAPI RenderObject : IRender
  {
  public:


    RenderObject(std::string name = "RenderObject");
    ~RenderObject();
    void UnBind();
    virtual void Render(Material& material, int mode = 4)override;
    virtual void Create(float* vertices, uint32_t size, uint32_t* data, uint32_t count);

    std::string m_name;
    unsigned int m_textureID;
    glm::vec4 m_color;
    Transform m_transform;
  protected:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexbuffer;


  };

  class GBAPI Sprite : public RenderObject
  {

  public:
    Sprite(uint32_t textID);
    ~Sprite();
  };

}