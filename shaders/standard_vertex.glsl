#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 i_color;

out vec3 FragColor;

void main(){
    FragColor = i_color;
    gl_Position = vec4(pos, 1.0);
}
