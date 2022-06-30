#version 430 core
layout( location = 0 ) in vec4 Position;
layout( location = 1 ) in vec4 Normal;
layout( location = 2 ) in vec3 Tangent;
layout( location = 3 ) in vec2 TexCoord;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Perspective;
uniform mat4 lightMVP;
out vec4 FragPosition;
out vec4 FragNormal;
out vec2 FragUV;
out vec4 lightSpacePos;
out mat3 TBN;
void main()
{
    vec4 Pos=Perspective*View*Model*Position;
    lightSpacePos=lightMVP*Model*Position;
    gl_Position = Pos;
    FragPosition=Position;
    FragNormal.xyz = normalize(mat3(Model)*Normal.xyz);//transpose(inverse(mat3(Model)))*Normal.xyz;
    FragNormal.w=0;
    FragUV=TexCoord;

    vec3 T=normalize(vec3(Model*vec4(Tangent,0)));
    vec3 N=normalize(FragNormal.xyz);
    vec3 B=cross(T,N);
    TBN=mat3(T,B,N);
}
