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
	//openglֻ��ʾgl_Position��x,y,zֵ����[-1��1]�ĵ㣬
		//͸��ͶӰ�У���Ҫ��͸��ͶӰ׶��̨�強ѹƽ��ת����[-1,1]^3�Ŀռ���
	float top = zNear * tan(radians(fov) / 2);
	float bottom = -top;
	float right = top * ratio;
	float left = -right;
	//ͶӰ glm�о����������ȴ洢,������Ҫת��һ��
	//ƽ��
	mat4 translate = transpose(mat4(1, 0, 0, -(right + left) / 2, 0, 1, 0, -(top + bottom) / 2,
		0, 0, 1, -(zNear + zFar) / 2, 0, 0, 0, 1));
	//��һ����[-1,1]^3�ռ���
	mat4 normalize = transpose(mat4(2 / (right - left), 0, 0, 0, 0, 2 / (top - bottom), 0, 0,
		0, 0, 2 / (zFar - zNear), 0, 0, 0, 0, 1));
	//��ѹ���󣬽�͸��ͶӰת��Ϊƽ��ͶӰ�ľ���
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
	//ת��(��������ת��Ϊ��)ǰ�ľ���*�۲�����ϵ����=��������ϵ��������ô��(ת��)����*ʱ������ϵ����=�۲�����ϵ����
	//����������㶼Ϊ��Ӧ����ϵԭ�㣬��������ת���ȼ���λ������ת��
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
	//ת��(��������ת��Ϊ��)ǰ�ľ���*�۲�����ϵ����=��������ϵ��������ô��(ת��)����*ʱ������ϵ����=�۲�����ϵ����
	//����������㶼Ϊ��Ӧ����ϵԭ�㣬��������ת���ȼ���λ������ת��
	return y;
}
vec3 Camero::getUpDir()
{
	return upDir;
}
