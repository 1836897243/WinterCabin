#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include<unordered_map>
using namespace std;
using namespace glm;
/*
* 与摄像机有关的类，可以设置摄像机的参数以及透视投影参数获得相关矩阵
*/
class Camero
{
public:
	Camero();
	void setCameroPos(vec3 Pos);
	void setPerspective(float _fov, float _ratio, float zNear, float _zFar);
	void setView(vec3 _upDir, vec3 _target);
	mat4 getPerspective();
	mat4 getView();
	vec3 getCameroPos();
	vec3 getTarget();
	vec3 getYDir();
	vec3 getUpDir();
private:
	vec3 CameroPos=vec3(0,0,0);
	vec3 upDir=vec3(0,1,0);
	vec3 targetDir =vec3(0,0,1);
	float fov = 45.f;
	float ratio = 1.f;
	float zNear = 0.1f;
	float zFar = 50.f;
};

