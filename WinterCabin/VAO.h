#pragma once
#include<vector>
#include<string>
#include"global.h"
#include"Camero.h"
#include"Material.h"
/*
* 保存了一个顶点数组对象，以及这个顶点数组对象的相关材质
*/
class VAO
{
public:
	VAO(vector<Vertex>vertices,vector<unsigned int>indicies,Material mtl)
		:meshData(vertices,indicies), Mtl(mtl)
	{
		mat4 mat = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
		MS = mat;
		MR = mat;
		MT = mat;
		Model = mat;
	}
	VAO(MeshData mesh, Material mtl)
		:meshData(mesh), Mtl(mtl)
	{
		mat4 mat = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
		MS = mat;
		MR = mat;
		MT = mat;
		Model = mat;
	}
public:
	void Rotate(mat4 R);
	void Scale(mat4 S);
	void Tranlate(mat4 T);
public:
	void toInitState()
	{
		mat4 mat = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
		MS = mat;
		MR = mat;
		MT = mat;
		Model = mat;
	}
	void Init(bool isDepth, GLuint shaderProgram);
	void updateUniform(GLuint shaderProgram);
	void Draw(GLuint shaderProgram);
private:
	//放缩，旋转，位移矩阵矩阵，表示物体状态
	mat4 MS;
	mat4 MR;
	mat4 MT;
	mat4 Model;
public:
	MeshData meshData;
	Material Mtl;
	enum{Position,Normal,Tangent,TexCoord};
	GLuint VaoId=0;
	GLuint VboId=0;
	GLuint EboId=0;
	GLuint MapKaId = 0;
	GLuint MapKdId = 0;
	GLuint MapKsId = 0;
	GLuint MapBumpId = 0;
	GLuint MapNsId = 0;
};

