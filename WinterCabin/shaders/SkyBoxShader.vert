#version 430 core
layout (location = 0) in vec3 aPos;
 
out vec3 TexCoords;
 
uniform mat4 Projection;
uniform mat4 View;

void main()
{
    TexCoords = aPos;
    vec4 pos = Projection * View * vec4(aPos, 1.0);
    gl_Position = pos.xyww;//保持深度为1，为最远
}