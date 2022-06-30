#include"Scene.h"
#include"GeometryGenerator.h"

int main(int argc, char** argv)
{
	GeometryGenerator GG;
	//创建立方体
	MeshData Box = GG.CreateBox(1, 1, 1, 1);
	Box.CalcTangent();
	Material mtl(vec3(0), vec3(1.), vec3(0.633, 0.727811, 0.633), 0.6);
	mtl.setMapKa("texture/Box.png");
	mtl.setMapKd("texture/Box.png");
	mtl.setMapKs("texture/Box_Ks2.png");
	mtl.setMapBump("texture/Texture_Norm.png");
	VAO vao(Box.Vertices, Box.Indices, mtl);
	Obj tmp;
	tmp.groups.push_back(vao);
	Scene::Objects.push_back(tmp);

	//创建地形
	MeshData Terrain = GG.CreateTerrain(1000, 1000, 25, 8, 2, 0.5, 100);
	Material mtl4(vec3(0.9215, 0.9745, 0.9215), vec3(0.50568, 0.505424, 0.455568), vec3(0.233, 0.227811, 0.233), 10);
	mtl4.setMapKa("texture/SnowField.jpg");
	mtl4.setMapKd("texture/SnowField.jpg");
	mtl4.setMapBump("texture/SnowNormal2.jpg");
	VAO vao4(Terrain.Vertices, Terrain.Indices, mtl4);
	Obj tmp4;
	tmp4.groups.push_back(vao4);
	Scene::Objects.push_back(tmp4);
	//导入房屋1
	Obj house;
	house.LoadObjFile("resources\\medieval-house", "stoneHouse");
	house.Tranlate(mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(10, 1, 0, 1)));
	Scene::Objects.push_back(house);
	//导入房屋2
	Obj house2;
	house2.LoadObjFile("resources\\old-house", "old_house");
	house2.Tranlate(mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, -0.5, 7, 1)));
	float angle = 3 * PI / 2;
	house2.Rotate(mat4(vec4(cos(angle), 0, -sin(angle), 0), vec4(0, 1, 0, 0), vec4(-sin(angle), 0, cos(angle), 0), vec4(0, 0, 0, 1)));
	Scene::Objects.push_back(house2);
	//导入树1
	Obj Tree;
	Tree.LoadObjFile("resources\\Tree", "Tree1",make_pair(true,10));
	Tree.Tranlate(mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(9, -1, 8, 1)));
	Scene::Objects.push_back(Tree);
	//导入树2
	Obj Tree2;
	Tree2.LoadObjFile("resources\\Tree", "Tree2", make_pair(true, 10));
	Tree2.Tranlate(mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(20, -1, 0, 1)));
	Scene::Objects.push_back(Tree2);
	//导入树3
	Obj Tree3;
	Tree3.LoadObjFile("resources\\Tree", "Tree3", make_pair(true, 10));
	Tree3.Tranlate(mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(-3, -1, -3, 1)));
	Scene::Objects.push_back(Tree3);
	//导入树4
	Obj Tree4;
	Tree4.LoadObjFile("resources\\Tree", "Tree4", make_pair(true, 10));
	Tree4.Tranlate(mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(13, -1, 13, 1)));
	Scene::Objects.push_back(Tree4);
	Scene::Cam.setCameroPos(vec3(1, 10, -1));
	Scene::Cam.setView(vec3(0, 1, 0), vec3(0, 0, 1));
	Scene::Cam.setPerspective(45,1920.f/1080.f, 0.1, 100);
	//导入雪人
	Obj SnowMan;
	SnowMan.LoadObjFile("resources\\SnowMan", "SnowMan");
	SnowMan.Tranlate(mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(7, -0.9, 10, 1)));
	Scene::Objects.push_back(SnowMan);
	//导入路灯
	Obj lamp;
	lamp.LoadObjFile("resources\\streetLight", "StreetLight",make_pair(true,8));
	lamp.Tranlate(mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(12, -1., 10, 1)));
	Scene::Objects.push_back(lamp);

	Camero lightInfo;
	lightInfo.setCameroPos(vec3(5, 20,0));
	lightInfo.setPerspective(150, 1, 0.1, 100);
	lightInfo.setView(vec3(1, 0, 0), vec3(0, -1, 0));
	Scene::light = Light(0.5f,0.8f,lightInfo,vec3(1),vec3(1),vec3(1));
	//天空盒
	vector<string>skyTexture = { "texture/elyvisions/dark_rt.png",
		"texture/elyvisions/dark_lf.png",
		"texture/elyvisions/dark_up.png",
		"texture/elyvisions/dark_dn.png",
		"texture/elyvisions/dark_ft.png",
		"texture/elyvisions/dark_bk.png" };
	Scene::skybox = SkyBox(skyTexture);
	Scene::run(argc, argv);
}