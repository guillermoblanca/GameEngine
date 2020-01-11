//vertex shader for OpenGL
#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

out vec2 v_TextCoord;
uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_proj;
void main()
{
	gl_Position = u_proj * u_view * u_transform * (vec4(position, 1.));
	v_TextCoord = texCoords;
}

//fragment shader for OpenGL
#shader fragment
#version 330 core
out vec4 color;
void main()
{
	color = vec4(0, 0, 1, 1);
}