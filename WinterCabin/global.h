#pragma once
#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include<functional>
#include"Camero.h"

#define PI 3.1415926
/*
* ����ļ������˺ܶ���/�ṹ�壬��Щ����������࣬Ϊ�˷�ֹ�����ļ�������̫ӷ�ף��Ͷ��ŵ�һ���ļ�
*/
/*
* ����ṹ�壬�����˺ܶඥ���λ�ã����㷨�ߣ����߿ռ�������������������
*/
struct Vertex
{
	Vertex(float px, float py, float pz, float nx, float ny, float nz,float Tx,float Ty,float Tz, float u, float v)
	{
		Position = vec3(px, py, pz);
		Normal = vec3(nx, ny, nz);
		Tagent = vec3(Tx, Ty, Tz);
		TexCoord = vec2(u, v);
	}
	Vertex(vec3 Pos=vec3(0), vec3 Nor= vec3(0),vec3 tagent= vec3(0),vec2 Tex= vec2(0, 0))
		:Position(Pos),Normal(Nor), Tagent(tagent),TexCoord(Tex)
	{}
	vec3 Position;
	vec3 Normal;
	vec3 Tagent;
	vec2 TexCoord;
	
};
struct MeshData
{
	MeshData(vector<Vertex> _Vertices= {}, vector<GLuint> _Indices={})
		:Vertices(_Vertices),Indices(_Indices){}
	MeshData(const MeshData&other)
		:Vertices(other.Vertices), Indices(other.Indices) {}
	void transform(mat4 mat)
	{
		for (unsigned i = 0; i < Vertices.size(); i++)
		{
			vec4 tmp = vec4(Vertices[i].Position, 1);
			tmp = mat*tmp;
			Vertices[i].Position.x = tmp.x / tmp.w;
			Vertices[i].Position.y = tmp.y / tmp.w;
			Vertices[i].Position.z = tmp.z / tmp.w;
			tmp = vec4(Vertices[i].Normal, 0);
			tmp = mat * tmp;
			Vertices[i].Normal.x = tmp.x;
			Vertices[i].Normal.y = tmp.y;
			Vertices[i].Normal.z = tmp.z;
		}
	}
	//���߿ռ����https://learnopengl-cn.github.io/05%20Advanced%20Lighting/04%20Normal%20Mapping/#_3
	void CalcTangent()
	{
		vector<vector<int>> hashIndex(Vertices.size());
		for (int i = 0; i < Indices.size(); i++)
			hashIndex[Indices[i]].push_back(i);
		function<float(vec3, vec3, vec3)> calcAngle = [](vec3 a, vec3 b, vec3 c) {return acos(dot(normalize(b - a), normalize(c - a)));};
		
		for (int i = 0; i < hashIndex.size(); i++)
		{
			float SumAngle = 0;
			Vertices[i].Tagent = vec3(0, 0, 0);
			for (int j = 0; j < hashIndex[i].size(); j++)
			{
				Vertex a, b, c;
				int index = hashIndex[i][j];
				if (index % 3 == 0)
				{
					a = Vertices[Indices[index]];
					b = Vertices[Indices[index + 2]];
					c = Vertices[Indices[index + 1]];
				}
				else if (index % 3 == 1)
				{
					a = Vertices[Indices[index]];
					b = Vertices[Indices[index - 1]];
					c = Vertices[Indices[index + 1]];
				}
				else if (index % 3 == 2)
				{
					a = Vertices[Indices[index]];
					b = Vertices[Indices[index - 1]];
					c = Vertices[Indices[index - 2]];
				}
				vec2 DelUv1 = b.TexCoord - a.TexCoord;
				vec2 DelUv2 = c.TexCoord - a.TexCoord;
				vec3 Edge1 = b.Position - a.Position;
				vec3 Edge2 = c.Position - a.Position;
				float f = 1.0f / (DelUv1.x * DelUv2.y - DelUv2.x*DelUv1.y);
				vec3 tangent;
				tangent.x = f * (DelUv2.y * Edge1.x - DelUv1.y * Edge2.x);
				tangent.y = f * (DelUv2.y * Edge1.y - DelUv1.y * Edge2.y);
				tangent.z = f * (DelUv2.y * Edge1.z - DelUv1.y * Edge2.z);
				tangent =normalize(tangent);
				float angle = calcAngle(a.Position, b.Position, c.Position);
				SumAngle += angle;
				Vertices[i].Tagent += tangent * angle;
			}
			Vertices[i].Tagent /= SumAngle;
		}
	}
	vector<Vertex> Vertices;
	vector<GLuint> Indices;
};
/*
* ��Դ���ԣ�������Դλ�ã�ͶӰ���ԣ����Լ�Ka,Kd��Ks����
*/
struct Light
{
	//https://www.cnblogs.com/zhxmdefj/p/11365819.html
	Light(float Ia, float I, Camero Info, vec3 ka, vec3 kd, vec3 ks)
		:IntensityAmbient(Ia), Intensity(I), PhysicalInfo(Info),Ka(ka),Kd(kd),Ks(ks)
	{}
	float IntensityAmbient = 0.5;
	float Intensity = 0.5;
	Camero PhysicalInfo;
	vec3 Ka = vec3(0, 0, 0);
	vec3 Kd = vec3(0, 0, 0);
	vec3 Ks = vec3(0, 0, 0);
};
//������Ϣ
struct TextureData
{
	TextureData(string Path,bool isfilp);
	~TextureData();
	int w;
	int h;
	int c;
	unsigned char* data;
};

