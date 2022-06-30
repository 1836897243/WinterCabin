#pragma once
#include"Camero.h"
#include <fstream>
#include<sstream> 
#include<functional>
/*
* 录取Obj文件的mtl材质，目前支持的属性有Ka,Kd,Ks,Ns,map_Ka,map_Kd,map_Ks,map_bump(只是最简单的法线贴图),(虽然有成员变量map_Ns,但还没搞清楚vec3属性的Ns
*怎么在光照模型中用)
*/
class Material {
public:
	Material(vec3 ka = vec3(0), vec3 kd = vec3(0), vec3 ks = vec3(0), float ns = 0, string Name = "null");
	Material(const Material& mtl);
	~Material() {}
	static vector<Material> loadMate(string Path, string Name);
	void setMapKa(string Path);
	void setMapKd(string Path);
	void setMapKs(string Path);
	string getMapKa();
	string getMapKd();
	string getMapKs();
	void setMapBump(string Path);
	string getMapBump();
	void setMapNs(string Path);
	string getMapNs();
	int getMtlKind();



	enum { MapKa = 1, MapKd = 2, MapKs = 4, MapBump = 8, MapNs = 16 };
	vec3 Ka;//环境
	vec3 Kd;//漫反射
	vec3 Ks;//镜面反射
private:
	string MapKaPath;
	string MapKdPath;
	string MapKsPath;
	string MapNsPath;
	string MapBumpPath;
public:
	float Ns;//镜面反射光泽
	int MtlKind;
	string MtlName;
};
