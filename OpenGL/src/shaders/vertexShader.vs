#version  330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTexture;
out vec2 TextCord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
gl_Position =projection*view*model*vec4(aPos,1.0f);
TextCord = vec2(aTexture.x,aTexture.y);
}