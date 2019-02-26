#include "gbpch.h"
#include "Render.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "VertexArray.h"
#include "IndexBuffer.h"

void GB::Render::Init()
{
	GB_CORE_INFO("Initialized Render class");

	const float positions[]
	{
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.5f, 0.5f,
		-0.5f, 0.5f,
	};
	unsigned int indices[]
	{
		0,1,2,
		2,3,0
	};
	

	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(indices, 6);
	material.CreateShader("Assets/Shader/Uniform.shader");
	material.CreateColor("u_Color");
	
	//bind

//	va.Bind();
	//ib.Bind();
}
//todo: pasar a eventcallback y quitarlo
void GlClearError()
{
	while (GLenum GL_Error = glGetError())
	{
		GB_CORE_ERROR("GL ERROR {0}", GL_Error);
	}
}
void GB::Render::Draw() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0.5f, 0.5f, 1);
	material.SetColor(Color(1, 0, 0));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
