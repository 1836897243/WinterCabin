#pragma once
#include"Camero.h"
#include <fstream>
#include<sstream> 
#include<functional>
/*
* ¼ȡObj�ļ���mtl���ʣ�Ŀǰ֧�ֵ�������Ka,Kd,Ks,Ns,map_Ka,map_Kd,map_Ks,map_bump(ֻ����򵥵ķ�����ͼ),(��Ȼ�г�Ա����map_Ns,����û�����vec3���Ե�Ns
*��ô�ڹ���ģ������)
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
	vec3 Ka;//����
	vec3 Kd;//������
	vec3 Ks;//���淴��
private:
	string MapKaPath;
	string MapKdPath;
	string MapKsPath;
	string MapNsPath;
	string MapBumpPath;
public:
	float Ns;//���淴�����
	int MtlKind;
	string MtlName;
};
