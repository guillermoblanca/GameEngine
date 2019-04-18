#include "gbpch.h"
#include "Material.h"
#include "glad\glad.h"
namespace GB
{

	unsigned int GB::LoadShaders(const std::string path)
	{
		char infoLog[1024];
		unsigned int vShaderID = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		GB::ShaderProgramSource source = GB::ParseShader(path);


		//compilado de vertex shader
		char const * vShaderPointer = source.VertexSource.c_str();
		glShaderSource(vShaderID, 1, &vShaderPointer, NULL);
		glCompileShader(vShaderID);

		//todo: implementar comprobacion
		int isCompiled;
		glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled ==GL_FALSE)
		{
			int maxLenght= GL_MAX_NAME_LENGTH;
			glGetShaderInfoLog(vShaderID, maxLenght, &maxLenght, infoLog);
			GB_CORE_ERROR("Vertex shader error: {0}", infoLog);
		}
		//compilado de fragment shader
		char const * fShaderPointer = source.FragmentSource.c_str();
		glShaderSource(fShaderID, 1, &fShaderPointer, NULL);
		glCompileShader(fShaderID);

		glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLenght = GL_MAX_NAME_LENGTH;
			glGetShaderInfoLog(fShaderID, maxLenght, &maxLenght, infoLog);
			GB_CORE_ERROR("Fragment shader error: {0}", infoLog);
		}
		//binding 
		unsigned int programID = glCreateProgram();
		glAttachShader(programID, vShaderID);
		glAttachShader(programID, fShaderID);
		glLinkProgram(programID);
		glValidateProgram(programID);
		//todo: implementar revision

		glDetachShader(programID, vShaderID);
		glDetachShader(programID, fShaderID);

		glDeleteShader(vShaderID);
		glDeleteShader(fShaderID);
		return programID;
	}

	ShaderProgramSource ParseShader(const std::string& filePath)
	{
		std::ifstream stream(filePath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)type] << line << '\n';
			}


		}
		ShaderProgramSource shader;
		shader.VertexSource = ss[0].str();
		shader.FragmentSource = ss[1].str();

		return shader;
	}

	void Material::SetVector3(const std::string loc, float x, float y, float z)
	{
		unsigned int location = glGetUniformLocation(shader, loc.c_str());
		GB_ASSERT(location == -1, "Shader uniform!");
		glUniform3f(location, x, y, z);
		
	}
	void Material::SetVector2(const std::string loc, float x, float y)
	{
		//todo: fix
		unsigned int location = glGetUniformLocation(shader, loc.c_str());
		GB_ASSERT(location == -1, "Shader uniform!");
		glUniform2f(location, x, y);
	}
	void Material::SetFloat(const std::string loc, float x)
	{
		unsigned int location = glGetUniformLocation(shader, loc.c_str());
		GB_ASSERT(location == -1, "Shader uniform failed!");
		glUniform1f(location, x);
	}
	void Material::SetInt(const std::string loc, int x)
	{
		unsigned int location = glGetUniformLocation(shader, loc.c_str());
		GB_ASSERT(location == -1, "Shader uniform failed!");
		glUniform1i(location, x);
	}
	void Material::SetVector4(const std::string loc, float x, float y, float z, float w)
	{
		unsigned int location = glGetUniformLocation(shader, loc.c_str());
		GB_ASSERT(location == -1, "Shader uniform failed!");
		glUniform4f(location, x, y, z, w);
	}
	void Material::SetMat4(const std::string loc, glm::mat4 mat)
	{
		unsigned int location = glGetUniformLocation(shader, loc.c_str());
		GB_ASSERT(location == -1, "Shader uniform failed!");
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	}
	Material::Material()
	{
		GB_CORE_INFO("Don't forget to use createshader for initialice process!");
	}
	Material::Material(const std::string path)
	{
		bool r = CreateShader(path);
		GB_CORE_ASSERT(r, "Material not created");
	}
	Material::~Material()
	{
		glDeleteProgram(shader);
	}

	bool Material::CreateShader(const std::string path)
	{
		shader = LoadShaders(path.c_str());
		glUseProgram(shader);

		return shader != -1; 
	}
	
	void Material::Bind()
	{
		glUseProgram(shader);
	}

}