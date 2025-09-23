
#version 330 core

in vec3 FragColor;
out vec4 color;

uniform float frame;

float getPulse(){
    return (sin(frame * 0.01f) + 1)/2;
}

void main(){
    color = vec4(FragColor, 1.0f) * getPulse();
}

