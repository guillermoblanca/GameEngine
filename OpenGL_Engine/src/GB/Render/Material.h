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

	class Material
	{

	public:
		Material();
		Material(const std::string path);
		~Material();



		bool CreateShader(const std::string path);
		void Bind();

		void SetVector3(const std::string loc, float x, float y, float z);
		void SetVector2(const std::string loc, float x, float y);
		void SetFloat(const std::string loc, float x);
		void SetInt(const std::string loc, int x);
		void SetVector4(const std::string loc, float x, float y, float z, float w);
		void SetMat4(const std::string loc, glm::mat4 mat);

	protected:
		unsigned int shader;
	};

}