#pragma once
#include "GB\Core.h"
#include "GB/Math.h"
#include "Material.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Mesh.h"
//#include "GB\GameplayFramework\Transform.h"
#include "..\GameplayFramework\Components\Transform.h"


namespace GB
{
 
  class GBAPI IRender
  {
  public:
    virtual void Render(int mode = 4) = 0;
  };


  class GBAPI RenderObject :public IRender
  {
  public:

	
    RenderObject(Material* mat,std::string name = "RenderObject");
    ~RenderObject();
    void UnBind();
    virtual void Render(int mode = 4)override;
    virtual void Create(float* vertices, uint32_t size, uint32_t* data, uint32_t count);
	virtual void Create(std::vector<glm::vec3>& vertices,std::vector<uint32_t>& verticesIndices);
	//Sustitute the old mesh if exist
	virtual void Create(Mesh& newMesh);
    ////
    // Debug
    ////


    std::string m_name;
	Mesh* mesh;
    int m_textureID;
    glm::vec4 m_color;
	Material* material;

    Transform m_transform;

  protected:
    std::shared_ptr<VertexArray> m_vertexArray;
  };

#pragma region Primitives

  class GBAPI Sprite : public RenderObject
  {

  public:
    Sprite(Material* mat,uint32_t textID, const std::string name = "Sprite");
    ~Sprite();
  };


  class Cube : public RenderObject
  {
  public:
    Cube(Material* mat, uint32_t textID, const std::string name = "Cube");
    ~Cube();

    virtual void Render(int mode = 4)override;

  };

  class Line : public RenderObject
  {
  public:
    Line(Material* mat,const vector2& origin,const vector2& destiny);
    virtual void Render(int mode = 4)override;


    vector2 position;
    vector2 destiny;

  protected:
    std::shared_ptr<VertexArray> m_vertexArray;
    
  };
#pragma endregion

}