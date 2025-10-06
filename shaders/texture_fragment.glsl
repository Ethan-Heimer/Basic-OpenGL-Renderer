#version 330 core
in vec3 FragColor;
in vec2 TexCord;

out vec4 color;

uniform sampler2D Texture;

void main(){
    color = texture(Texture, TexCord) * vec4(FragColor, 0);
}
