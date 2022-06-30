#include "SkyBox.h"
#include"LoadShaders.h"
SkyBox::SkyBox(vector<string> TexPaths)
    :faces(TexPaths)
{
    skyboxVertices = {
        // positions          
        vec3(-1.0f, 1.0f, -1.0f),
        vec3(-1.0f, -1.0f, -1.0f),
        vec3(1.0f, -1.0f, -1.0f),
        vec3(1.0f, -1.0f, -1.0f),
        vec3(1.0f,  1.0f, -1.0f),
        vec3(-1.0f,  1.0f, -1.0f),

        vec3(-1.0f, -1.0f,  1.0f),
        vec3(-1.0f, -1.0f, -1.0f),
        vec3(-1.0f,  1.0f, -1.0f),
        vec3(-1.0f,  1.0f, -1.0f),
        vec3(-1.0f,  1.0f,  1.0f),
        vec3(-1.0f, -1.0f,  1.0f),

        vec3(1.0f, -1.0f, -1.0f),
        vec3(1.0f, -1.0f,  1.0f),
        vec3(1.0f,  1.0f,  1.0f),
        vec3(1.0f,  1.0f,  1.0f),
        vec3(1.0f,  1.0f, -1.0f),
        vec3(1.0f, -1.0f, -1.0f),

        vec3(-1.0f, -1.0f,  1.0f),
        vec3(-1.0f,  1.0f,  1.0f),
        vec3(1.0f,  1.0f,  1.0f),
        vec3(1.0f,  1.0f,  1.0f),
        vec3(1.0f, -1.0f,  1.0f),
        vec3(-1.0f, -1.0f,  1.0f),

        vec3(-1.0f,  1.0f, -1.0f),
        vec3(1.0f,  1.0f, -1.0f),
        vec3(1.0f,  1.0f,  1.0f),
        vec3(1.0f,  1.0f,  1.0f),
        vec3(-1.0f,  1.0f,  1.0f),
        vec3(-1.0f,  1.0f, -1.0f),

        vec3(-1.0f, -1.0f, -1.0f),
        vec3(-1.0f, -1.0f,  1.0f),
        vec3(1.0f, -1.0f, -1.0f),
        vec3(1.0f, -1.0f, -1.0f),
        vec3(-1.0f, -1.0f,  1.0f),
        vec3(1.0f, -1.0f,  1.0f),
    };
}

void SkyBox::init()
{
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "shaders/SkyBoxShader.vert"},
        { GL_FRAGMENT_SHADER, "shaders/SkyBoxShader.frag"},
        { GL_NONE, NULL }
    };
    Shader = LoadShaders(shaders);
    glUseProgram(Shader);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1, &VboId);
    glBindBuffer(GL_ARRAY_BUFFER,VboId);
    glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(vec3), &skyboxVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(0));
    glEnableVertexAttribArray(0);

    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        TextureData Data(faces[i],false);
        if (Data.data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGBA, Data.w, Data.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data.data
            );
        }
        else
        {
            cout << "»ñÈ¡Ìì¿ÕºÐÎÆÀíÊ§°Ü" << endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void SkyBox::Draw(mat4 View, mat4 Projection, float lightAmbient)
{
    glDepthFunc(GL_LEQUAL);
    glUseProgram(Shader);
    GLint loc = glGetUniformLocation(Shader, "View");
    assert(loc >= 0);
    View = mat4(mat3(View));//ÒÆ³ýÎ»ÒÆ
    glUniformMatrix4fv(loc, 1, GL_FALSE, &View[0][0]);
    loc = glGetUniformLocation(Shader, "Projection");
    assert(loc >= 0);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &Projection[0][0]);
    
    loc = glGetUniformLocation(Shader, "lightAmbient");
    assert(loc >= 0);
    glUniform1f(loc, lightAmbient);

    glBindVertexArray(VaoId);
    glBindVertexArray(VboId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    loc = glGetUniformLocation(Shader, "skybox");
    glUniform1i(loc, 0);
    glDrawArrays(GL_TRIANGLES, 0, skyboxVertices.size());
    glDepthFunc(GL_LESS);

}
