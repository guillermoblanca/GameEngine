#shader vertex
#version 330 core

layout(location = 0 ) in vec3 position;

void main()
{
	gl_Position.xyz = position;
	gl_Position.w = 1.0;
}

#shader fragment
#version 330 core
out vec4 color;
void main()
{
	color = vec4(1,0,1,1);
}