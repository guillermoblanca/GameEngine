#shader vertex
#version 330 core

layout(location = 0 ) in vec3 position;
layout(location = 1 ) in vec2 texCoords;

out vec2 v_TextCoord;
void main()
{
	gl_Position.xyz = position;
	gl_Position.w = 1.0;
	v_TextCoord = texCoords;
}

#shader fragment
#version 330 core
layout(location =0) out vec4 color;
in vec2 v_TextCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{
	vec4 texColor = texture(u_Texture,v_TextCoord );
	color =  texColor;
}