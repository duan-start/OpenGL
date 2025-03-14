#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform float iTime;
uniform vec2 iResolution;

#define t iTime
#define r iResolution.xy

void main() {
   	vec3 c;
	float l,z=t;
	for(int i=0;i<3;i++) {
		vec2 uv,p=abs(TexCoords.xy);
		uv=p;
		p-=.5;
		p.x*=r.x/r.y;
		z+=.07;
		l=length(p);
		uv+=p/l*(sin(z)+1.)*abs(sin(l*9.-z-z));
		c[i]=.01/length(mod(uv,1.)-.5);
	}
	FragColor=vec4(c/l,t);
}