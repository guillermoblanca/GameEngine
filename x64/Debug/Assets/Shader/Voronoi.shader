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

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_TextCoord;

uniform vec2 iResolution;
uniform vec4 u_Color;
uniform float iTime;
uniform sampler2D u_Texture;

vec2 N22(vec2 p)
{
	vec3 a = fract(p.xyx*vec3(123.34, 234.34, 345.65));
	a += dot(a, a + 34.45);
	return fract(vec2(a.x*a.y, a.y*a.z));
}

void main()
{
	vec2 uv = (v_TextCoord - iResolution.xy) / iResolution.y;
	float m = 0.;
	float t = iTime;
	float minDist = 100.;
	float cellIndex = 0;

	

		for (float i = 0.; i < 50; i++)
		{
			vec2 n = N22(vec2(i));
			vec2 p = sin(n*t);

			float d = length(uv - p);
			m += smoothstep(.05, .03, d);

			if (d < minDist)
			{
				minDist = d;
				cellIndex = i;
			}
		}
		vec4 vor = vec4(vec3(minDist), 1.0);
		color = texture(u_Texture, v_TextCoord)* u_Color *vor;



	//if(color.r == 0.0f && color.g == 0.0f && color.b == 0.0f) color.r =1.0f;
	//color =  vec4(1.0,0.0,0.0,1.0);
}