#version  330 core
in vec3 ourColor;
out vec4 FragColor;

uniform float objectColor;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
in vec2 TextCord;

void main (){
    FragColor=mix(texture(ourTexture, TextCord),
    texture(ourTexture2,vec2(1.0-TextCord .x,TextCord.y)),0.2)*vec4(objectColor,ourColor);
    }