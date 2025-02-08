#version  330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform Material material;

in vec3 FragPos;
in vec3 Normal;
void main (){

    // ambient lighting
   vec3 ambient = light.ambient *texture(material.diffuse, TexCoords).rgb ;

   // diffuse lighting
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(light.position - FragPos);

   float diff = max(dot(norm,lightDir), 0.0f);
   vec3 diffuse =  light.diffuse*diff * texture(material.diffuse, TexCoords).rgb;
   // specular lighting
   
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);

   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular*(spec * texture(material.specular, TexCoords).rgb);


    FragColor=vec4(ambient+diffuse+specular,1.0f);
    }