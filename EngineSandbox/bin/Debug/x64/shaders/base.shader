#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 texCoords;

struct MVP{
   mat4 model;
   mat4 view;
   mat4 projection;
};

uniform MVP uni_MVP;

void main(){
    texCoords = aTexCoords;
    gl_Position = uni_MVP.projection * uni_MVP.view * uni_MVP.model * vec4(aPos, 1.0f);
};

#shader fragment
#version 330 core
out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;

void main(){
    fragColor = texture(texture_diffuse1, texCoords);
};