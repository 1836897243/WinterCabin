#pragma once
#include"global.h"
/*
* ��պУ�init,Draw�ĵ��÷�ʽ��obj�ļ��е�ͬ��������ʽ����
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

