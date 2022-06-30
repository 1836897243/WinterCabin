#include "Scene.h"
#include"LoadShaders.h"
void Scene::genDepthMap(GLuint*& depthMapFBO, GLuint*& depthMap, GLuint SHADOW_WIDTH, GLuint SHADOW_HEIGHT)
{
	glGenFramebuffers(1, depthMapFBO); //����һ��֡�������

	glGenTextures(1, depthMap);
	glBindTexture(GL_TEXTURE_2D, *depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthMap, 0);
	//���ò������κ���ɫ
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Scene::RenderShadow()
{
	glViewport(0, 0, 1024, 1024);
	glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthMap, 0);
	glDrawBuffer(GL_NONE);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(DepthShader);
	GLint loc = glGetUniformLocation(DepthShader, "lightMVP");
	assert(loc >= 0);
	mat4 MatInfo1 = light.PhysicalInfo.getPerspective() * light.PhysicalInfo.getView();
	glUniformMatrix4fv(loc, 1, GL_FALSE, &MatInfo1[0][0]);

	for (unsigned i = 0; i < Objects.size(); i++)
	{
		Objects[i].DepthFrameDraw(DepthShader);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Scene::RenderObjects()
{
	//��ȡ�������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.8f, .8f, .8f, 1.f);



	glUseProgram(Shader);
	glDrawBuffer(GL_FRONT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *depthMap);
	GLint loc = glGetUniformLocation(Shader, "shadowMap");
	assert(loc >= 0);
	glUniform1i(loc, 0);

	
	
	float iResolution[2];
	iResolution[0] = glutGet(GLUT_WINDOW_WIDTH);
	iResolution[1] = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, iResolution[0], iResolution[1]);

	
	//���¹�����ز���
	loc = glGetUniformLocation(Shader, "IntensityAmbient");
	assert(loc >= 0);
	glUniform1f(loc, light.IntensityAmbient);
	loc = glGetUniformLocation(Shader, "Intensity");
	assert(loc >= 0);
	glUniform1f(loc, light.Intensity);
	loc = glGetUniformLocation(Shader, "LightPos");
	assert(loc >= 0);
	vec3 lightPos = light.PhysicalInfo.getCameroPos();
	glUniform3f(loc, lightPos[0], lightPos[1], lightPos[2]);
	loc = glGetUniformLocation(Shader, "lightMVP");
	assert(loc >= 0);
	mat4 MatInfo = light.PhysicalInfo.getPerspective() * light.PhysicalInfo.getView();;
	glUniformMatrix4fv(loc, 1, GL_FALSE, &MatInfo[0][0]);

	loc = glGetUniformLocation(Shader, "LightKa");
	assert(loc >= 0);
	glUniform3f(loc, light.Ka[0], light.Ka[1], light.Ka[2]);
	loc = glGetUniformLocation(Shader, "LightKd");
	assert(loc >= 0);
	glUniform3f(loc, light.Kd[0], light.Kd[1], light.Kd[2]);
	loc = glGetUniformLocation(Shader, "LightKs");
	assert(loc >= 0);
	glUniform3f(loc, light.Ks[0], light.Ks[1], light.Ks[2]);


	loc = glGetUniformLocation(Shader, "CameroPos");
	assert(loc >= 0);
	vec3 CameroPos = Cam.getCameroPos();
	glUniform3f(loc, CameroPos[0], CameroPos[1], CameroPos[2]);
	loc = glGetUniformLocation(Shader, "View");
	assert(loc >= 0);
	mat4 MatV = Cam.getView();
	glUniformMatrix4fv(loc, 1, GL_FALSE, &MatV[0][0]);
	loc = glGetUniformLocation(Shader, "Perspective");
	assert(loc >= 0);
	mat4 MatP = Cam.getPerspective();
	glUniformMatrix4fv(loc, 1, GL_FALSE, &MatP[0][0]);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	for (unsigned i = 0; i < Objects.size(); i++)
	{
		Objects[i].Draw(Shader);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Scene::RenderSkyBox()
{
	skybox.Draw(Cam.getView(),Cam.getPerspective(), light.IntensityAmbient);
}
//ÿ20ms���û���һ��
void Scene::drive(int data)
{
	glutTimerFunc(20, drive, 1);
	glutPostRedisplay();
}
void Scene::display()
{

	//cout << "Pos(" << Cam.getCameroPos()[0] << "," << Cam.getCameroPos()[1] << "," << Cam.getCameroPos()[2] << endl;// "," <<
	//���²���,����Ч��
	float iTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
	const float R = 20.f;
	const float T = 120.f;
	float theta = iTime * 2.f * PI / T;
	theta = glm::mod((double)theta, 2.f * PI);
	vec3 pos;
	if (theta < PI)
	{
		pos = vec3(cos(theta) * R, sin(theta) * R, 0);
		light.PhysicalInfo.setCameroPos(pos);
		float iResolution[2];
		iResolution[0] = glutGet(GLUT_WINDOW_WIDTH);
		iResolution[1] = glutGet(GLUT_WINDOW_HEIGHT);
		light.PhysicalInfo.setPerspective(150, iResolution[0] / iResolution[1], 0.1, 80);
		light.PhysicalInfo.setView(vec3(0, 0, 1), vec3(0, 0, 0) - pos);
		light.Intensity = glm::max(0.5f * dot(vec3(0, 1, 0), normalize(pos)), 0.f);
		light.IntensityAmbient = light.Intensity + 0.2f;
		light.Kd = vec3(1);
	}
	else
	{
		pos = vec3(10.806, 5.25367, 10.0413);
		light.PhysicalInfo.setCameroPos(pos);
		light.PhysicalInfo.setView(vec3(1, 0, 0), vec3(0, -1, 0));
		light.PhysicalInfo.setPerspective(90, 1, 0.1, 10);
		light.Intensity = 0.4;
		light.IntensityAmbient = 0.3f;
		light.Kd = vec3(0.8, 0.8, 0.5);
	}
	
	RenderShadow();
	RenderObjects();
	RenderSkyBox();
	glutSwapBuffers();
	
}
void Scene::init()
{
	//���������޳� ��Ĭ�ϱ����޳���
	//glEnable(GL_CULL_FACE);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//�����
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

	// detect current settings
	GLint iMultiSample = 0;
	GLint iNumSamples = 0;
	glGetIntegerv(GL_SAMPLE_BUFFERS, &iMultiSample);
	glGetIntegerv(GL_SAMPLES, &iNumSamples);
	printf("MSAA on, GL_SAMPLE_BUFFERS = %d, GL_SAMPLES = %d\n", iMultiSample, iNumSamples);
	string VertShader, FragShader;

	VertShader = "shaders/Shader.vert";
	FragShader = "shaders/Shader.frag";

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, VertShader.c_str()},
		{ GL_FRAGMENT_SHADER, FragShader.c_str()},
		{ GL_NONE, NULL }
	};
	Shader = LoadShaders(shaders);
	VertShader = "shaders/depthShader.vert";
	FragShader = "shaders/depthShader.frag";
	ShaderInfo Depthshaders[] = {
		{ GL_VERTEX_SHADER, VertShader.c_str()},
		{ GL_FRAGMENT_SHADER, FragShader.c_str()},
		{ GL_NONE, NULL }
	};
	DepthShader = LoadShaders(Depthshaders);
	depthMapFBO = new GLuint;
	depthMap = new GLuint;
	genDepthMap(depthMapFBO, depthMap, 1024, 1024);
	for (unsigned i = 0; i < Objects.size(); i++)
		Objects[i].Init(false,Shader);
	for (unsigned i = 0; i < Objects.size(); i++)
		Objects[i].Init(true, DepthShader);
	skybox.init();
}
void Scene::SpecialFunc(int key, int x, int y)
{
	
}
void Scene::KeyboardFunc(unsigned char key, int x, int y)
{
	vec3 pos = Cam.getCameroPos();
	vec3 target = vec3(0);
	//����W��A,S,D������������ƶ���W,S��ǰ���ƶ���A,D�������ƶ�
	switch (key)
	{
	case 'W':
	case 'w':
	{
		target = Cam.getTarget();
		pos += vec3(0.3) * normalize(target);
		break;
	}
	case 'S':
	case 's':
	{
		target = Cam.getTarget();
		pos -= vec3(0.3) * normalize(target);
		break;
	}
	case 'A':
	case 'a':
	{
		target = Cam.getTarget();
		vec3 y = Cam.getYDir();
		pos += vec3(0.3) * normalize(cross(target,y));
		break;
	}
	case 'D':
	case 'd':
	{
		target = Cam.getTarget();
		vec3 y = Cam.getYDir();
		pos -= vec3(0.3f) * normalize(cross(target, y));
		break;
		break;
	}
	}
	Cam.setCameroPos(pos);
}

void Scene::mouse_hit(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:	//���������
		if (state == GLUT_DOWN)	//�������ʱ
		{
			lastMousePos.x = x;
			lastMousePos.y = y;
			ButtonState = GLUT_DOWN;
			ButtonKind = button;
		}
		else if (state == GLUT_UP)
		{
			ButtonKind = -1;
			ButtonState = GLUT_UP;
		}
		break;
	case GLUT_RIGHT_BUTTON:	//�Ҽ�������
		if (state == GLUT_DOWN)	//�������ʱ
		{
			lastMousePos.x = x;
			lastMousePos.y = y;
			ButtonState = GLUT_DOWN;
			ButtonKind = button;
		}
		else if (state == GLUT_UP)
		{
			ButtonKind = -1;
			ButtonState = GLUT_UP;
		}
		break;
		break;
	default:
		break;
	}
}


//һ��Ĭ��CAmero.upDir=vec3(0,1,0)
void Scene::mouse_move(int x, int y)
{
	//�������������ڰ���״̬���������굱ǰλ��������ϴ�λ��֮��������������
	//��������ƶ�����������Ͽ��������ƶ���������¿��������ƶ���������󿴣������ƶ���������ֿ�
	if (ButtonKind== GLUT_LEFT_BUTTON&&ButtonState == GLUT_DOWN)
	{
		float dx = 0.005f * (x - lastMousePos.x);
		float dy = 0.005f *	(y - lastMousePos.y);
		mat3 rotateY = mat3(vec3(cos(dx),0,-sin(dx)),vec3(0,1,0), vec3(sin(dx),0, cos(dx)));
		mat3 rotateX = mat3(vec3(1, 0, 0), vec3(0,cos(dy), sin(dy)), vec3(0,-sin(dy), cos(dy)));
		vec3 Z = normalize(Cam.getTarget());
		vec3 X = normalize(cross(Cam.getUpDir(), Z));
		vec3 Y = cross(Z, X);
		//��x����ת
		mat3 R = mat3(X, Y, Z);
		Z = R*rotateX*vec3(0,0,1);
		Y = cross(Z, X);
		//��ֹĿ�귽����UpDirһ��
		if(dot(Z,Cam.getUpDir())<1-0.00001)
			Cam.setView(Cam.getUpDir(), Z);
		//��y����ת
		Z = normalize(Cam.getTarget());
		X = normalize(cross(Cam.getUpDir(), Z));
		Y = cross(Z, X);
		R = mat3(X, Y, Z);
		Z = R * rotateY * vec3(0, 0, 1);
		Y = cross(Z, X);
		//��ֹĿ�귽����UpDirһ��
		if (dot(Z, Cam.getUpDir()) < 1 - 0.00001)
			Cam.setView(Cam.getUpDir(), Z);
		
		lastMousePos.x = x;
		lastMousePos.y = y;
	}//������Ҽ����£��������굱ǰλ��������ϴ�λ��֮����������λ�ã�����������ӽǣ��������������ƶ�
	else if (ButtonKind == GLUT_RIGHT_BUTTON && ButtonState == GLUT_DOWN)
	{
		float dx = 0.05f * (-x + lastMousePos.x);
		float dy = 0.05f * (-y + lastMousePos.y);
		vec3 TargetDir = Cam.getTarget();
		vec3 Xaxis = normalize(cross(vec3(0, 1, 0), TargetDir));
		vec3 Yaxis = normalize(cross(Xaxis, TargetDir));
		vec3 CameroPos = Cam.getCameroPos();
		CameroPos += dx * Xaxis;
		CameroPos += dy * Yaxis;
		Cam.setCameroPos(CameroPos);
		lastMousePos.x = x;
		lastMousePos.y = y;
	}
}

void Scene::run(int argc, char** argv)
{
	glutInit(&argc, argv);
	//�����
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE| GLUT_MULTISAMPLE);//ָ��glueCreatWindow�����Ĵ���ģʽ
	glutInitWindowSize(1920, 1080);//����glutCraetWindow�����Ĵ��ڵĴ�С
	glutInitContextVersion(4, 3);//ָ��������Ⱦ����ʹ�õ�Opengl�汾
	glutInitContextProfile(GLUT_CORE_PROFILE);//GLUT_CORE_PROFILE����ģʽ��GLUT_COMPATIBILITY_PROFILE����ģʽ
	glutCreateWindow(argv[0]);//��������
	if (glewInit()) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
	init();
	glutDisplayFunc(display);//���ûص�������ÿ�θ��´��������Զ�����display����
	glutTimerFunc(20, drive, 1);
	glutSpecialFunc(SpecialFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(mouse_hit);
	glutMotionFunc(mouse_move);
	glutMainLoop();//�¼�����ѭ������Զ�����أ���Ӧ�¼�����ʱ��Ϊʱ��ע��Ļص�������������
}
vector<Obj> Scene::Objects = vector<Obj>(0);
Camero Scene::Cam = Camero();
Light Scene::light = Light(0.5, .5, Camero(), vec3(0), vec3(0), vec3(0));
ivec2 Scene::lastMousePos=ivec2(0,0);
GLuint Scene::DepthShader = 0;
GLuint Scene::Shader = 0;
GLuint* Scene:: depthMapFBO=nullptr;//֡�������
GLuint* Scene:: depthMap = nullptr;//֡����ID
int Scene::ButtonState = GLUT_UP;;
int Scene::ButtonKind=-1;
SkyBox Scene::skybox = SkyBox({});
