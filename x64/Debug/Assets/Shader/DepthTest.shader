#shader vertex
#version 330 core

layout(location = 0 ) in vec3 position;
layout(location = 1 ) in vec2 texCoords;

out vec2 v_TextCoord;
uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_proj;
void main()
{
	gl_Position =  u_proj * u_view * u_transform * (vec4(position,1.));
	v_TextCoord = texCoords;
}

#shader fragment
#version 330 core
layout(location =0) out vec4 color;
in vec2 v_TextCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
float near = 0.1;
float far = 100.0;
float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1;
	return (2.0 * near * far) / (far + near - z) * (far - near));

}
void main()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	color = texture(u_Texture,v_TextCoord)* u_Color;

	//if(color.r == 0.0f && color.g == 0.0f && color.b == 0.0f) color.r =1.0f;
	//color =  vec4(1.0,0.0,0.0,1.0);
}