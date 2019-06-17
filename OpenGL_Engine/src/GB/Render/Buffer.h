#pragma once
#include "GB/Core.h"

namespace GB
{
  enum class EShaderDataType : uint8_t
  {
    None = 0, Mat3, Mat4, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Bool
  };

  static uint32_t ShaderDataTypeSize(EShaderDataType type)
  {
    switch (type)
    {
    case EShaderDataType::Mat3:   return 4 * 3 * 3;
    case EShaderDataType::Mat4:   return 4 * 4 * 4;
    case EShaderDataType::Float:  return 4;
    case EShaderDataType::Float2: return 4 * 2;
    case EShaderDataType::Float3: return 4 * 3;
    case EShaderDataType::Float4: return 4 * 3;
    case EShaderDataType::Int:    return 4;
    case EShaderDataType::Int2:   return 4 * 2;
    case EShaderDataType::Int3:   return 4 * 3;
    case EShaderDataType::Int4:   return 4 * 4;
    case EShaderDataType::Bool:   return 1;
    }
    //    GB_CORE_ASSERT(false, "Uknow ShaderDataType");
    return 0;
  }
  struct BufferElement
  {
    std::string Name;
    EShaderDataType Type;
    uint32_t Size;
    uint32_t Offset;
    bool Normalized;

    BufferElement(){}
    BufferElement(EShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
    {

    }
    uint32_t GetComponentCount()const
    {
      switch (Type)
      {
      case EShaderDataType::Int: return  1;
      case EShaderDataType::Int2: return 2;
      case EShaderDataType::Int3: return 3;
      case EShaderDataType::Int4: return 4;
      case EShaderDataType::Float: return 1;
      case EShaderDataType::Float2: return 2;
      case EShaderDataType::Float3: return 3;
      case EShaderDataType::Float4: return 4;
      case EShaderDataType::Mat3: return 3*3;
      case EShaderDataType::Mat4: return 4*4;
      case EShaderDataType::Bool: return 1;
      case EShaderDataType::None: return 0;
      }
      //GB_CORE_ASSERT(false, "Get element Counts unknow");
      return 0;

    }

  };
  class BufferLayout
  {
  public:
    BufferLayout(){}
    BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements)
    {
      CalculateOffsetAndStride();
    }
    inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    inline uint32_t GetStride() const { return m_Stride; }
    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
  private:
    void CalculateOffsetAndStride()
    {
      uint32_t offset = 0;
      m_Stride = 0;
      for (auto& element : m_Elements)
      {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
      }
    }
  private:
    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride = 0;
  };

  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() {}

    virtual void Bind()   const = 0;
    virtual void UnBind() const = 0;
    virtual void SetLayout(const BufferLayout& layout) = 0;
    virtual BufferLayout GetLayout()const = 0;
    static VertexBuffer* Create(float* vertices, uint32_t size);
  };

  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() {}

    virtual void Bind()   const = 0;
    virtual void UnBind() const = 0;

    virtual uint32_t GetCount()const = 0;
    static IndexBuffer* Create(uint32_t* indices, uint32_t count);
  };
}