#pragma once
#include "GB\Core.h"
#include "Texture.h"
#include "glm\glm.hpp"


namespace GB
{
	unsigned int LoadShaders(const std::string path);

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	ShaderProgramSource ParseShader(const std::string& filePath);
	//todo: not sure

	class Material
	{

	public:
		~Material();



		void CreateShader(const std::string path);
		void Bind();

		void SetVector3(const std::string loc, float x, float y, float z);
		void SetVector2(const std::string loc, float x, float y);
		void SetFloat(const std::string loc, float x);
		void SetInt(const std::string loc, int x);
		void SetVector4(const std::string loc, float x, float y, float z, float w);
		void SetMat4(const std::string loc, glm::mat4 mat);

		inline Texture* GetTexture(unsigned const int id)  { return m_textures[id]; }

		void AddTexture(Texture *tex);
		inline void RemoveTexture(unsigned const int id) { m_textures.erase(m_textures.begin() + id); }
	protected:
		std::vector<Texture*> m_textures;
		unsigned int shader;
	};

}