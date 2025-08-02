#version 330 core

in vec3 FragPos;
in vec3 norm;

out vec4 color;

uniform vec3 objectColor;

void main()
{
    vec3 lightPos = vec3(10, 20, 0);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 lightColor = vec3(1, 1, 1);
    
    vec3 normal = normalize(norm);

    vec3 ambient = vec3(0.1);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * lightColor;
    
    vec3 final = (ambient + diffuse) * objectColor;
    color = vec4(final, 1.0);
}


