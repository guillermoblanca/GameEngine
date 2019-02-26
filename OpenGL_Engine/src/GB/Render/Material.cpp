#include "gbpch.h"
#include "Material.h"
#include "glad\glad.h"
namespace GB
{

	unsigned int GB::LoadShaders(const std::string path)
	{
		unsigned int vShaderID = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		GB::ShaderProgramSource source = GB::ParseShader(path);


		//compilado de vertex shader
		char const * vShaderPointer = source.VertexSource.c_str();
		glShaderSource(vShaderID, 1, &vShaderPointer, NULL);
		glCompileShader(vShaderID);

		//todo: implementar comprobacion

		//compilado de fragment shader
		char const * fShaderPointer = source.FragmentSource.c_str();
		glShaderSource(fShaderID, 1, &fShaderPointer, NULL);
		glCompileShader(fShaderID);

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

	ShaderProgramSource GB::ParseShader(const std::string& filePath)
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

	void Material::SetColor(Color color)
	{
		glUniform4f(colorLocation, color.r, color.g, color.b, color.a);
	}

	void Material::CreateColor(const std::string color)
	{
		colorLocation = glGetUniformLocation(shader, color.c_str());
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