#version 430 core
layout( location = 0 ) in vec4 Position;
layout( location = 1 ) in vec4 Normal;
layout( location = 2 ) in vec2 TexCoord;
uniform mat4 lightMVP;
uniform mat4 Model;
void main()
{
    gl_Position = lightMVP*Model*Position;
}