#pragma once

#pragma region Includes
#include "GB\Core.h"

#include "Material.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "GB\ComponentSystem\Transform.h"
#pragma endregion


namespace GB
{
 
  class GBAPI IRender
  {
  public:
    virtual void Render(Material& material, int mode = 4) = 0;
  };


  class GBAPI RenderObject :public IRender
  {
  public:


    RenderObject(std::string name = "RenderObject");
    ~RenderObject();
    void UnBind();
    virtual void Render(Material& material, int mode = 4)override;
    virtual void Create(float* vertices, uint32_t size, uint32_t* data, uint32_t count);
    
    ////
    // Debug
    ////


    std::string m_name;
    
    ////
    //Render properties
    ////

    int m_textureID;
    glm::vec4 m_color;
 
    ////
    // Position/Rotation/Scale
    ////
    Transform m_transform;

  protected:
    std::shared_ptr<VertexArray> m_vertexArray;
  };

#pragma region Primitives

  class GBAPI Sprite : public RenderObject
  {

  public:
    Sprite(uint32_t textID, const std::string name = "Sprite");
    ~Sprite();
  };


  class Cube : public RenderObject
  {
  public:
    Cube(uint32_t textID, const std::string name = "Cube");
    ~Cube();
  };
#pragma endregion

}