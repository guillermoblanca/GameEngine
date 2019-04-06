#shader vertex
#version 330 core

layout(location = 0 ) in vec3 position;
layout(location = 1 ) in vec2 texCoords;

void main()
{
	gl_Position = vec4(position,1.0f);
	
}

#shader fragment
#version 330 core
layout(location = 0 ) out vec4 color;
uniform float u_resolution;

vec2 GridTile(vec2 _st,float zoom)
{
	_st *= zoom;
	_st.x += step(1.0,mod(_st.y,1.0));
	return fract(_st);
}
float Box(vec2 _st,vec2 _size)
{
	 _size = vec2(0.5)-_size*0.5;
    vec2 uv = smoothstep(_size,_size+vec2(1e-4),_st);
    uv *= smoothstep(_size,_size+vec2(1e-4),vec2(1.0)-_st);
    return uv.x*uv.y;
}
void main()
{
	vec2 st = gl_FragCoord.xy / vec2(u_resolution).xy;
	vec3 _color = vec3(0.0);

	st = GridTile(st,5.0);
	
	_color =vec3(Box(st,vec2(0.9)));

	color = vec4(_color,1.0);
}