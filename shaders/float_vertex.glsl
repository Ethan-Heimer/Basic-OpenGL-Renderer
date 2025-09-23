#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 i_color;

uniform float frame;

out vec3 FragColor;

float getOffset(){
    return sin(frame * 0.01) * .25;
}

void main(){
    FragColor = i_color;
    gl_Position = vec4(pos.x, pos.y + getOffset(), pos.z, 1.0);
}
