#include "Camero.h"

Camero::Camero()
{
}

void Camero::setCameroPos(vec3 Pos)
{
	CameroPos = Pos;
}

void Camero::setPerspective(float _fov, float _ratio, float _zNear, float _zFar)
{
	fov = _fov;
	ratio = _ratio;
	zNear = _zNear;
	zFar = _zFar;
}

void Camero::setView(vec3 _upDir, vec3 _targetDir)
{
	upDir = _upDir;
	targetDir = _targetDir;
}

mat4 Camero::getPerspective()
{
	//opengl只显示gl_Position的x,y,z值属于[-1，1]的点，
		//透视投影中，需要把透视投影锥形台体挤压平移转化到[-1,1]^3的空间中
	float top = zNear * tan(radians(fov) / 2);
	float bottom = -top;
	float right = top * ratio;
	float left = -right;
	//投影 glm中矩阵按照列优先存储,所以需要转置一下
	//平移
	mat4 translate = transpose(mat4(1, 0, 0, -(right + left) / 2, 0, 1, 0, -(top + bottom) / 2,
		0, 0, 1, -(zNear + zFar) / 2, 0, 0, 0, 1));
	//归一化到[-1,1]^3空间中
	mat4 normalize = transpose(mat4(2 / (right - left), 0, 0, 0, 0, 2 / (top - bottom), 0, 0,
		0, 0, 2 / (zFar - zNear), 0, 0, 0, 0, 1));
	//挤压矩阵，将透视投影转换为平行投影的矩阵
	mat4 squeeze = transpose(mat4(zNear / zFar, 0, 0, 0, 0, zNear / zFar, 0, 0,
		0, 0, (zNear + zFar) / zFar, -zNear, 0, 0, 1 / zFar, 0));
	return  normalize * translate * squeeze;
}

mat4 Camero::getView()
{
	mat4 translate = transpose(mat4(1, 0, 0, -CameroPos[0], 0, 1, 0, -CameroPos[1],
		0, 0, 1, -CameroPos[2], 0, 0, 0, 1));
	vec3 z = normalize(targetDir);
	vec3 x = normalize(cross(upDir, z));
	vec3 y = cross(z, x);
	//转置(正交矩阵，转置为逆)前的矩阵*观察坐标系向量=世界坐标系向量，那么逆(转置)矩阵*时间坐标系向量=观察坐标系向量
	//由于向量起点都为对应坐标系原点，所以向量转换等价于位置坐标转换
	mat4 view = transpose(mat4(x[0], x[1], x[2], 0, y[0], y[1], y[2], 0, z[0], z[1], z[2], 0, 0, 0, 0, 1));
	return view * translate;
}

vec3 Camero::getCameroPos()
{
	return CameroPos;
}

vec3 Camero::getTarget()
{
	return targetDir;
}

vec3 Camero::getYDir()
{
	mat4 translate = transpose(mat4(1, 0, 0, -CameroPos[0], 0, 1, 0, -CameroPos[1],
		0, 0, 1, -CameroPos[2], 0, 0, 0, 1));
	vec3 z = normalize(targetDir);
	vec3 x = normalize(cross(upDir, z));
	vec3 y = cross(z, x);
	//转置(正交矩阵，转置为逆)前的矩阵*观察坐标系向量=世界坐标系向量，那么逆(转置)矩阵*时间坐标系向量=观察坐标系向量
	//由于向量起点都为对应坐标系原点，所以向量转换等价于位置坐标转换
	return y;
}
vec3 Camero::getUpDir()
{
	return upDir;
}
