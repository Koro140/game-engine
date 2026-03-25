#version 460

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TextureCoord;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(a_Position, 1, 1);
    TexCoord = a_TextureCoord;
}