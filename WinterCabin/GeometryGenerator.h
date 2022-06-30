//***************************************************************************************
// GeometryGenerator.h by Frank Luna (C) 2011 All Rights Reserved.
//   
// Defines a static class for procedurally generating the geometry of 
// common mathematical objects.
//
// All triangles are generated "outward" facing.  If you want "inward" 
// facing triangles (for example, if you want to place the camera inside
// a sphere to simulate a sky), you will need to:
//   1. Change the Direct3D cull mode or manually reverse the winding order.
//   2. Invert the normal.
//   3. Update the texture coordinates and tangent vectors.
//***************************************************************************************

#pragma once

#include"global.h"
/*
* ����һ�����ɻ�����������࣬�������������壬���壬�Լ�Բ̨�����Σ�ƽ��
*/
class GeometryGenerator
{
public:
	//����һ��������
	MeshData CreateBox(float width, float height, float depth, uint32 numSubdivisions);
	//����һ������
	MeshData CreateSphere(float radius, uint32 sliceCount, uint32 stackCount);
	//����һ��Բ̨
	MeshData CreateCylinder(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount);
	//�ο�the book of shader �еķ��β����˶��γɵ���
	//https://thebookofshaders.com/13/?lan=ch
	MeshData CreateTerrain(float length = 10, float width = 10, float hight = 25, int octaves = 8, float lacunarity = 2.0, float gain = 0.5, uint32 numSubdivisions = 10);
	//����һ��ƽ��
	MeshData CreatePlane(float length, float width, uint32 numSubdivisions);
private:
	void Subdivide(MeshData& meshData);
	Vertex MidPoint(const Vertex& v0, const Vertex& v1);
	void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount, MeshData& meshData);
	void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount, MeshData& meshData);
	float random(vec2 st);
	vec2 random2(vec2 st);
	float ValueNoise(vec2 st);
	float GradientNoise(vec2 st);
	float fbm(vec2 st, int octaves = 8, float lacunarity = 2.0, float gain = 0.5, uint32 numSubdivisions = 10, float amplitude = 0.5,float frequency = 1.);
};

