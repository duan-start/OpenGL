#version  330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {  
    vec3 position;    // �����λ��  
    vec3 SpotDir;     // �����������  

    vec3 ambient;  
    vec3 diffuse;  
    vec3 specular;  

    float constant;  
    float linear;  
    float quadratic;  
    float cutoff;  
    float outercutoff;
};  

uniform Light light;
uniform Material material;

void main () {  
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    // Ambient���  
    vec3 ambient = attenuation * light.ambient * texture(material.diffuse, TexCoords).rgb;  

    // Diffuse���  
    vec3 norm = normalize(Normal);  
    vec3 lightDir = normalize(light.position - FragPos); // ��Ƭ��λ�õ���Դ�ķ���  

    float ins = light.cutoff-light.outercutoff;

    // ����۹�ƽǶ�  
    float theta = dot(lightDir, normalize(-light.SpotDir)); // ����н�  

    float intensity = clamp((theta-light.outercutoff)/ins,0.0,1.0);

    if (theta > light.outercutoff) {  
        float diff = max(dot(norm, lightDir), 0.0);  
        vec3 diffuse =3*intensity *attenuation * light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  

        // Specular���  
        vec3 viewDir = normalize(viewPos - FragPos);  
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  
        vec3 specular =intensity* attenuation * light.specular * (spec * texture(material.specular, TexCoords).rgb);  

        FragColor = vec4(ambient + diffuse + specular, 1.0);  
    } else {  
        FragColor = vec4(ambient, 1.0);  
    }  
}