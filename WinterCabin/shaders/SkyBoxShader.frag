#version 430 core
out vec4 FragColor;
 
in vec3 TexCoords;
 
uniform samplerCube skybox;
uniform float lightAmbient;
void main()
{    
    FragColor = lightAmbient*texture(skybox, TexCoords);
//    FragColor=vec4(abs(TexCoords),1);
}