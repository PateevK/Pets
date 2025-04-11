#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


struct MVP{
   mat4 model;
   mat4 view;
   mat4 projection;
};

uniform MVP uni_MVP;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;
void main(){
    fragPos = vec3(uni_MVP.model * vec4(aPos, 1.0f));
    normal = mat3(transpose(inverse(uni_MVP.model))) * aNormal;
    texCoord = aTexCoord;
    gl_Position = uni_MVP.projection * uni_MVP.view * uni_MVP.model * vec4(aPos, 1.0f);
}

#shader fragment
#version 330 core
out vec4 fragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};


struct DirLight{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 dir;
};

struct PointLight{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 pos;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 pos;
    float constant;
    float linear;
    float quadratic;
    vec3 dir;
    float innCutoff;
    float outCutoff;
};


vec3 calcDirLight(DirLight light, vec3 normal,vec3 fragPos, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal,vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal,vec3 fragPos, vec3 viewDir);

uniform vec3 camPos;
uniform Material material;
#define NR_LIGHTS 2
uniform SpotLight light[NR_LIGHTS];

void main(){
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(fragPos - camPos);
    vec3 result;
    for(int i = 0; i < NR_LIGHTS; i++){
    result += calcSpotLight(light[i], norm, fragPos, viewDir);
    }
    fragColor = vec4(result,1.0f);
    
};

vec3 calcSpotLight(SpotLight light, vec3 normal,vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(fragPos - light.pos);
    float diffuse_v = max(dot(normal, -lightDir), 0.0f);
    vec3 lightReflect = reflect(lightDir, normal);
    float specular_v = pow(max(dot(-viewDir, lightReflect),0.0f), material.shininess);
    float distance = length(light.pos - fragPos);
    float attenuation = 1/(light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
    float theta = dot(normalize(light.dir), lightDir);
    float epsilon = light.innCutoff - light.outCutoff;
    float intensity = clamp((theta - light.outCutoff) / epsilon, 0.0f, 1.0f);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diffuse_v * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * specular_v * vec3(texture(material.specular, texCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}


vec3 calcPointLight(PointLight light, vec3 normal,vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(fragPos - light.pos);
    float diffuse_v = max(dot(normal, -lightDir), 0.0f);
    vec3 lightReflect = reflect(lightDir, normal);
    float specular_v = pow(max(dot(-viewDir, lightReflect),0.0f), material.shininess);
    float distance = length(light.pos - fragPos);
    float attenuation = 1/(light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diffuse_v * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * specular_v * vec3(texture(material.specular, texCoord));
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
};


vec3 calcDirLight(DirLight light, vec3 normal,vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.dir);
    float diffuse_v =  max(dot(-lightDir, normal),0.0f);
    vec3 lightReflect = normalize(reflect(lightDir, normal)); 
    float specular_v = pow(max(dot(-lightReflect, viewDir),0.0f),material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diffuse_v * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * specular_v * vec3(texture(material.specular, texCoord));
    return (ambient + diffuse + specular);
};