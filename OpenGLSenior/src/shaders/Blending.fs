#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D texture1;

void main (){
    vec4 texColor=texture(texture1,TexCoords);
    //采样到的透明度较低，表明这个像素是透明的，我们要将其丢弃
    if(texColor.a<0.1)
        discard;
    FragColor = texColor;
}