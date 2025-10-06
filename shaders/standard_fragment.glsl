#version 330 core
in vec3 FragColor;
in vec2 TexCord;

out vec4 color;

void main(){
    color = vec4(FragColor, 0.0f);
}
