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
//layout (location =0) out vec4 color;

uniform vec4 u_Color;
uniform vec2 u_resolution;
uniform float u_size;
uniform float u_tone;

float plot(vec2 st, float pot)
{
return smoothstep(pot-0.02,pot,st.y)-smoothstep(pot, pot+0.02,st.y);
}
void main()
{
	//if(u_lenght ==0)u_lenght =1;
	vec2 st = gl_FragCoord.st/u_resolution;
	float y = st.x;
	vec3 colour = vec3(y);
	float pot = plot(st,y);
	colour =(u_tone-pot)*colour*pot*vec3(0.0,1.0,0.0);
    gl_FragColor = vec4(colour,1.0);
}
