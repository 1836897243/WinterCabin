#pragma once
#include "Obj.h"
#include "SkyBox.h"
using namespace std;
using namespace glm;

/*
* Ϊ��ֹ����main������̫�ң�����opengl��صĲ�����Ϣ�����Scene��
*/
static class Scene
{
private:
	static ivec2 lastMousePos;
	static int ButtonState;
	static int ButtonKind;
private:
	static GLuint DepthShader;
	static GLuint Shader;
	static GLuint*depthMapFBO;//֡�������
	static GLuint*depthMap;//֡����ID
private:
	static void genDepthMap(GLuint*& depthMapFBO, GLuint*& depthMap, GLuint SHADOW_WIDTH, GLuint SHADOW_HEIGHT);
	static void RenderShadow();
	static void RenderObjects();
	static void RenderSkyBox();
public:
	static Camero Cam;
	static Light light;
	static vector<Obj> Objects;
	static SkyBox skybox;

public:
	static void drive(int data);
	static void display();
	static void init();
	static void SpecialFunc(int key, int x, int y);
	static void KeyboardFunc(unsigned char key, int x, int y);
	static void mouse_hit(int button, int state, int x, int y);
	static void mouse_move(int x, int y);
	static void run(int argc, char** argv);
};

