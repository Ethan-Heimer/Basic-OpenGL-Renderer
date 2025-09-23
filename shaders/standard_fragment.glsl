#version 330 core
in vec3 FragColor;
out vec4 color;

void main(){
    color = vec4(FragColor, 0.0f);
}
