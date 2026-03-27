#version 460

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TextureCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform vec4 uvRect;

void main() {
    gl_Position = projection * model * vec4(a_Position, 0.0, 1.0);
    TexCoord = mix(uvRect.xy, uvRect.zw, a_TextureCoord);
}