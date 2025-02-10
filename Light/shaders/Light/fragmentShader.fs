#version  330 core  

out vec4 FragColor;  
uniform vec3 lightColor;

void main() {  
    FragColor =vec4(lightColor,1.0f); // 输出光源的颜色
}