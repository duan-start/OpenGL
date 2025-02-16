#version 330 core
out vec4 FragColor;

float near = 0.1; 
float far  = 100.0; 

in vec2 TexCoords;
uniform sampler2D texture1;
//float LinearizeDepth(float depth) 
//{
//    float z = depth * 2.0 - 1.0; // ת��Ϊ NDC
//    return (2.0 * near * far) / (far + near - z * (far - near));    
//}

void main()
{             
    //float depth = LinearizeDepth(gl_FragCoord.z) / far; // Ϊ����ʾ���� far
    //FragColor = vec4(vec3(depth), 1.0);

    FragColor= vec4(texture(texture1,TexCoords));
}