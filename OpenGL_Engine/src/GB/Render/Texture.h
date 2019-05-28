#pragma once
#include "gbpch.h"
#include "GB\Core.h"
#include "Platform\stb\stb_image.h"
//todo: fix opengl dependencies
class  Texture
{
public:
	Texture(const std::string path, unsigned int pos = 0);
	~Texture();

	void Bind(unsigned int slot =0)const;
	void UnBind()const;
	inline std::string GetPath() const { return m_FilePath; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const{ return m_Height; }
	inline int GetBPP() const { return m_BPP; }
	inline unsigned int GetID() { return m_ID; }
private:
	unsigned int m_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width;
	int m_Height;
	int m_BPP;

};