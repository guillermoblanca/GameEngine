#pragma once
#include "GB\Core.h"
#include "Texture2D.h"
#include "glm\glm.hpp"


namespace GB
{
	unsigned int LoadShaders(const std::string path);

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

  /*Crear el shader desde un archivo de texto*/
	ShaderProgramSource ParseShader(const std::string& filePath);
  //todo: implementar la creacion de shader desde un string que sea el archivo directamente
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

		std::string& GetPath() { return currentpath; }
	protected:
		uint32_t shader;
		std::string currentpath;

	};

}