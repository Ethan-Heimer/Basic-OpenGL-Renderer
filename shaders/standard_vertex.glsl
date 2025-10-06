#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 i_color;
layout (location = 2) in vec2 i_texture;

out vec3 FragColor;
out vec2 TexCord;

void main(){
    FragColor = i_color;
    TexCord = i_texture;

    gl_Position = vec4(pos, 1.0);
}
