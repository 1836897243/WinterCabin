#include <fstream>
#include<sstream> 
#include "Obj.h"
void Obj::LoadObjFile(string path,string name,pair<bool,float>constrainHeight)//不带.obj（原名称要求.obj小写,.mtl小写）
{
	vector<vec3> Vs;
	vector<vec3> Vns;
	vector<vec2> Vtcs;
	//只能读 v,vt,vn,f(三角形面),mtl()
	unordered_map<string, Material>mtllib;
	unordered_map<string, vector<Vertex>>VaoVertices;
	unordered_map<string, vector<unsigned>>VaoIndices;
	unordered_map<string, unordered_map<string, unsigned>>ObjIndex2VaoIndex;
	string mtllibPath;
	string CurentMate;
	ifstream infile;
	string objFile = path + "\\" + name  + ".obj";
	infile.open(objFile, ios::in);
	if (!infile.is_open())
	{
		cout << path<<":打开模型失败" << endl;
		return;
	}
	while (!infile.eof())
	{
		string tmp;
		infile >> tmp;
		if (tmp != ""&&tmp[0]>='0'&&tmp[0]<='9')
		{
			cout << "Obj文件不符合全为三角形面要求" << endl;
			return;
		}
		if (tmp == "#")
		{
			getline(infile, tmp);
		}
		else if (tmp == "mtllib")
		{
			infile >> mtllibPath;
			//对mtl文件处理
		}
		else if (tmp == "usemtl")
		{
			infile >> CurentMate;
		}
		else if (tmp == "v")
		{
			float x, y, z;
			infile >> x;
			infile >> y;
			infile >> z;
			Vs.push_back(vec3(x, y, z));
		}
		else if (tmp == "vt")
		{
			float x, y, z;
			infile >> x;
			infile >> y;
			Vtcs.push_back(vec2(x, y));
		}
		else if (tmp == "vn")
		{
			float x, y, z;
			infile >> x;
			infile >> y;
			infile >> z;
			Vns.push_back(vec3(x, y, z));
		}
		else if (tmp == "f")
		{
			getline(infile, tmp);
			istringstream iss(tmp);
			vector<unsigned>indexs;
			while(iss>>tmp)
			{
				if (tmp == "#")
					break;
				int pos = tmp.find("/", 0);
				unsigned v = stoi(tmp.substr(0, pos));
				unsigned pos1 = tmp.find("/", pos+1);
				assert(pos1 >=pos + 1);
				unsigned vt=0;
				if(pos1 > pos + 1)
					vt= stoi(tmp.substr(pos + 1, pos1 - pos));
				assert(tmp.size() > pos + 1);
				int vn = stoi(tmp.substr(pos1+1, tmp.size()-1 - pos1));
				if (ObjIndex2VaoIndex[CurentMate].find(tmp) == ObjIndex2VaoIndex[CurentMate].end())
				{
					ObjIndex2VaoIndex[CurentMate][tmp] = VaoVertices[CurentMate].size();
					int tes2 = VaoVertices.size();
					VaoVertices[CurentMate].push_back(Vertex(Vs[v - 1], Vns[vn - 1],vec3(0),vt==0?vec2(0):Vtcs[vt - 1]));
				}
				indexs.push_back(ObjIndex2VaoIndex[CurentMate][tmp]);
			//	VaoIndices[CurentMate].push_back(ObjIndex2VaoIndex[CurentMate][tmp]);
			}
			for (unsigned i = 2; i < indexs.size(); i++)
			{
				VaoIndices[CurentMate].push_back(indexs[0]);
				VaoIndices[CurentMate].push_back(indexs[i-1]);
				VaoIndices[CurentMate].push_back(indexs[i]);
			}
		}
		else if(tmp!="")
			getline(infile, tmp);
	}
	infile.close();
	vector<Material>Mtls = Material::loadMate(path,name + ".mtl");
	for (unsigned i = 0; i < Mtls.size(); i++)
	{
		string mtlName = Mtls[i].MtlName;
		MeshData meshdata(VaoVertices[mtlName], VaoIndices[mtlName]);
		meshdata.CalcTangent();
		VAO newVao(meshdata, Mtls[i]);
		groups.push_back(newVao);
	}
	if (constrainHeight.first)
	{
		float minH = 100000, maxH = -100000;
		for (int k = 0; k < groups.size(); k++)
		{
			for (int i = 0; i < groups[k].meshData.Vertices.size(); i++)
			{
				minH = glm::min(groups[k].meshData.Vertices[i].Position.y, minH);
				maxH = glm::max(groups[k].meshData.Vertices[i].Position.y, maxH);
			}
		}

		float f = constrainHeight.second / (maxH - minH);
		for (int k = 0; k < groups.size(); k++)
		{
			for (int i = 0; i < groups[k].meshData.Vertices.size(); i++)
			{
				groups[k].meshData.Vertices[i].Position *= vec3(f);
			}
		}
	}
}
void Obj::Rotate(mat4 R)
{
	for (unsigned i = 0; i < groups.size(); i++)
		groups[i].Rotate(R);
}
void Obj::Scale(mat4 S)
{
	for (unsigned i = 0; i < groups.size(); i++)
		groups[i].Scale(S);
}
void Obj::Tranlate(mat4 T)
{
	for (unsigned i = 0; i < groups.size(); i++)
		groups[i].Tranlate(T);
}
void Obj::DepthFrameDraw(GLuint shaderProgram)
{
	for (unsigned i = 0; i < groups.size(); i++)
		groups[i].Draw(shaderProgram);
}
void Obj::Init(bool isDepth,GLuint shaderProgram)
{
	for (unsigned i = 0; i < groups.size(); i++)
		groups[i].Init(isDepth, shaderProgram);
}

void Obj::Draw(GLuint shaderProgram)
{
	for (unsigned i = 0; i < groups.size(); i++)
	{
		groups[i].updateUniform(shaderProgram);
		groups[i].Draw(shaderProgram);
	}
}
