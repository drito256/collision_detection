#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 norm;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);

    norm = mat3(transpose(inverse(model))) * aNorm;
}


