#version 330 core

in vec3 FragPos;
in vec3 norm;

uniform vec3 color;

out vec4 final_color;

void main()
{
    vec3 lightPos = vec3(0, 10, 0);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 lightColor = vec3(1, 1, 1);
    
    vec3 normal = normalize(norm);

    vec3 ambient = vec3(0.5);
    vec3 diffuse;
    if(color != vec3(0, 1, 0))
        diffuse = max(dot(normal, lightDir), 0.0) * lightColor;
    else
        diffuse = vec3(0);

    vec3 combined = (ambient + diffuse) * color;
    final_color = vec4(combined, 1.0);
}


