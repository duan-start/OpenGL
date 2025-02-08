#version  330 core
out vec4 FragColor;

uniform float RedValue;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
in vec2 TextCord;

void main (){
    FragColor=mix(texture(ourTexture,vec2(TextCord.x,1.0-TextCord.y)),
    texture(ourTexture2,vec2(1.0-TextCord .x,1.0-TextCord.y)),0.2)*vec4(RedValue,0.1f,0.2f,0.0f);
    }