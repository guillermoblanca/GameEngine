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
			int maxLenght=0;
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
			int maxLenght = 0;
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

	void MaterialParam::SetVector3(const std::string loc, float x, float y, float z)
	{
		unsigned int location = glGetUniformLocation(m_shader, loc.c_str());
		GB_ASSERT(location != -1, "Shader uniform!");
		glUniform3f(location, x, y, z);
		
	}
	void MaterialParam::SetVector2(const std::string loc, float x, float y)
	{
		//todo: fix
		unsigned int location = glGetUniformLocation(m_shader, loc.c_str());
//		GB_ASSERT(location != -1, "Shader uniform!");
		glUniform2f(location, x, y);
	}
	void MaterialParam::SetFloat(const std::string loc, float x)
	{
		unsigned int location = glGetUniformLocation(m_shader, loc.c_str());
		GB_ASSERT(location == -1, "Shader uniform failed!");
		glUniform1f(location, x);
	}
	void MaterialParam::SetInt(const std::string loc, int x)
	{
		unsigned int location = glGetUniformLocation(m_shader, loc.c_str());
		GB_ASSERT(location == -1, "Shader uniform failed!");
		glUniform1i(location, x);
	}
	void MaterialParam::SetVector4(const std::string loc, float x, float y, float z, float w)
	{
		unsigned int location = glGetUniformLocation(m_shader, loc.c_str());
		GB_ASSERT(location != -1, "Shader uniform failed!");
		glUniform4f(location, x, y, z, w);
	}
	void MaterialParam::SetMatrix(const std::string loc, Matrix * matrix)
	{
		GB_CORE_ERROR("Not defined SetMatrix!");
	}
	Material::~Material()
	{
		//todo: fix
		//glDeleteProgram(shader);
	}

	void Material::CreateShader(const std::string path)
	{
		shader = LoadShaders(path.c_str());
		glUseProgram(shader);

	}

	void Material::Bind()
	{
		glUseProgram(shader);
	}

	Color::Color()
	{
		r = g = b = 1;
		a = 0;
	}
	Color::Color(float _r, float _g, float _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}
	Color Color::Lerp(Color a, Color b, float time)
	{
		// a*(1-t) + b*t formula de interpolacion lineal
		time =  time <=0 ? 0 : time>= 1? 1: time;
		Color color;
		color.r = a.r *(1 - time) + b.r*time;
		color.g = a.g*(1 - time) + b.g *time;
		color.b = a.b*(1 - time) + b.b*time;
		color.a = a.a *(1 - time) + b.a*time;

		return color;
	}
}