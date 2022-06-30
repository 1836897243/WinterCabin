#pragma once
#include"global.h"
#include "VAO.h"
#include "Material.h"
/*
* ��������һ���������������Ϣ�������Vao��ɣ���openglˢ�º�����ֱ�ӵ���Draw,DepthFrameDraw��opengl ��ʼ��ʱ����init����
*/
class Obj
{
public:
	void LoadObjFile(string path,string name,pair<bool,float>constrainHight={false,0});
public:
	void Rotate(mat4 R);
	void Scale(mat4 S);
	void Tranlate(mat4 T);
public:
	void DepthFrameDraw(GLuint shaderProgram);
	void Init(bool isDepth,GLuint shaderProgram);
	void Draw(GLuint shaderProgram);
public:
	vector<VAO>groups;
private:
};

