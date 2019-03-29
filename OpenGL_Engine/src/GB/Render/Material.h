#pragma once
#include "GB\Core.h"
//todo: cargar por separado el shader del codigo 
//todo: cargar shader solo el string 
//todo: mejorar la carga de recursos

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
	struct Color
	{
		Color();
		Color(float _r, float _g, float _b);

		Color& operator =(const Color& other);
		Color operator +(const Color& other);
		Color operator -(const Color& other);

		static Color Red();
		static Color Blue();
		static Color Green();
		static Color Yellow();
		static Color White();
		static Color Black();
		static Color Purple();

		static Color Lerp(Color a, Color b, float time);
		static Color SLerp(Color a, Color b, float time);
		static Color Random(); //por investigar
		float*  ColorToFloat();
		int ColorToHex(); //devuelve el valor hexadecimal del color
		static Color HexToColor(int hexValue); //TODO: not working properly (fix)
		float r, g, b, a;
	};
	
	//todo define
	class Matrix;

	class MaterialParam
	{
	public:
		MaterialParam(unsigned int shader) : m_shader(shader){}

		void SetVector3(const std::string loc,float x, float y, float z);
		void SetVector2(const std::string loc,float x, float y);
		void SetFloat(const std::string loc, float x);
		void SetVector4(const std::string loc,float x, float y, float z, float w);
		void SetMatrix(const std::string loc, Matrix * matrix);
		
	private:
		unsigned int m_shader;
	};

	class Material
	{
	public:
		~Material();



		void CreateShader(const std::string path);
		inline MaterialParam GetParam() { return MaterialParam(shader); }
	private:
		unsigned int shader;
	};

}