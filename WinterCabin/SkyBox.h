#pragma once
#include"global.h"
/*
* 天空盒，init,Draw的调用方式与obj文件中的同名函数方式类似
*/
class SkyBox
{
public:
	SkyBox(vector<string>TexPaths);
	void init();
	void Draw(mat4 View,mat4 Projection,float lightAmbient);
private:
	vector<string>faces;
	GLuint textureID;
	GLuint Shader;
	GLuint VaoId;
	GLuint VboId;
	vector<vec3> skyboxVertices;
};

