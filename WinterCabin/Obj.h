#pragma once
#include"global.h"
#include "VAO.h"
#include "Material.h"
/*
* 这个类包含一个场景中物体的信息，有许多Vao组成，在opengl刷新函数中直接调用Draw,DepthFrameDraw，opengl 初始化时调用init函数
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

