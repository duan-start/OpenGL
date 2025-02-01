#version  330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexture;
out vec3 ourColor;
out vec2 TextCord;
uniform mat4 trans;
uniform mat4 size;
void main(){
gl_Position =size*trans*vec4(aPos,1.0f);
ourColor = aColor;
TextCord = vec2(aTexture.x,aTexture.y);
}