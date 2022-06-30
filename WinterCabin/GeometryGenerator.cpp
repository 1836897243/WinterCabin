//***************************************************************************************
// GeometryGenerator.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "GeometryGenerator.h"
#include <algorithm>
MeshData GeometryGenerator::CreateBox(float width, float height, float depth, GLuint numSubdivisions)
{
	MeshData meshData;
	Vertex v[24];

	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	// Fill in the front face vertex data.
	// Fill in the front face vertex data.
	v[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[2] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[3] = Vertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = Vertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[5] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[7] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[9] = Vertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[10] = Vertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[11] = Vertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = Vertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[13] = Vertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[14] = Vertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[15] = Vertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = Vertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[17] = Vertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[18] = Vertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[20] = Vertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[21] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[23] = Vertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	meshData.Vertices.assign(&v[0], &v[24]);

	//
	// Create the indices.
	//

	GLuint i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	meshData.Indices.assign(&i[0], &i[36]);

	// Put a cap on the number of subdivisions.
	numSubdivisions = std::min<GLuint>(numSubdivisions, 6u);

	for (GLuint i = 0; i < numSubdivisions; ++i)
		Subdivide(meshData);

	return meshData;
}

MeshData GeometryGenerator::CreateSphere(float radius, GLuint sliceCount, GLuint stackCount)
{
	MeshData meshData;

	//
	// Compute the vertices stating at the top pole and moving down the stacks.
	//

	// Poles: note that there will be texture coordinate distortion as there is
	// not a unique point on the texture map to assign to the pole when mapping
	// a rectangular texture onto a sphere.
	Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	meshData.Vertices.push_back(topVertex);

	float phiStep = (float)PI / stackCount;
	float thetaStep = 2.0f * (float)PI / sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (GLuint i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i * phiStep;

		// Vertices of ring.
		for (GLuint j = 0; j <= sliceCount; ++j)
		{
			float theta = j * thetaStep;

			Vertex v;

			// spherical to cartesian
			v.Position.x = radius * sinf(phi) * cosf(theta);
			v.Position.y = radius * cosf(phi);
			v.Position.z = radius * sinf(phi) * sinf(theta);

			v.Normal = normalize(v.Position);

			v.TexCoord.x = theta / (2* (float)PI);
			v.TexCoord.y = phi / (float)PI;

			meshData.Vertices.push_back(v);
		}
	}

	meshData.Vertices.push_back(bottomVertex);

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (GLuint i = 1; i <= sliceCount; ++i)
	{
		meshData.Indices.push_back(0);
		meshData.Indices.push_back(i + 1);
		meshData.Indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	GLuint baseIndex = 1;
	GLuint ringVerTexCoordount = sliceCount + 1;
	for (GLuint i = 0; i < stackCount - 2; ++i)
	{
		for (GLuint j = 0; j < sliceCount; ++j)
		{
			meshData.Indices.push_back(baseIndex + i * ringVerTexCoordount + j);
			meshData.Indices.push_back(baseIndex + i * ringVerTexCoordount + j + 1);
			meshData.Indices.push_back(baseIndex + (i + 1) * ringVerTexCoordount + j);

			meshData.Indices.push_back(baseIndex + (i + 1) * ringVerTexCoordount + j);
			meshData.Indices.push_back(baseIndex + i * ringVerTexCoordount + j + 1);
			meshData.Indices.push_back(baseIndex + (i + 1) * ringVerTexCoordount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	GLuint southPoleIndex = (GLuint)meshData.Vertices.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVerTexCoordount;

	for (GLuint i = 0; i < sliceCount; ++i)
	{
		meshData.Indices.push_back(southPoleIndex);
		meshData.Indices.push_back(baseIndex + i);
		meshData.Indices.push_back(baseIndex + i + 1);
	}

	return meshData;
}



MeshData GeometryGenerator::CreateTerrain(float length, float width, float hight, int octaves, float lacunarity, float gain, uint32 numSubdivisions)
{
	MeshData meshData;
	float dl = 1 / (float)numSubdivisions;
	float dw = 1 / (float)numSubdivisions;
	float dt = 1 / (float)numSubdivisions;
	for (unsigned i = 0; i <= numSubdivisions; i++)
	{
		for (unsigned j = 0; j <= numSubdivisions; j++)
		{
			Vertex tmp = Vertex(vec3(j*dw* width -0.5* width, hight*fbm(vec2(i * dl*10, j * dw*10)), i * dl* length - length * 0.5), vec3(0, 1, 0), vec3(0, 0, 0), vec2(i * dl*length, j * dw*width));
			meshData.Vertices.push_back(tmp);
		}
	}
	for (unsigned i = 0; i < numSubdivisions; i++)
	{
		for (unsigned j = 0; j < numSubdivisions; j++)
		{
			int index = i * (numSubdivisions + 1) + j;
			meshData.Indices.push_back(index);
			meshData.Indices.push_back(index + numSubdivisions + 1);
			meshData.Indices.push_back(index + numSubdivisions + 2);

			
			meshData.Indices.push_back(index);
			meshData.Indices.push_back(index + 1);
			meshData.Indices.push_back(index + (numSubdivisions + 2));
			
			if (i != 0 && j != 0)
			{
				vec3 n1 = cross(meshData.Vertices[index + numSubdivisions + 1].Position - meshData.Vertices[index].Position,
					meshData.Vertices[index + numSubdivisions + 2].Position - meshData.Vertices[index].Position);
				vec3 n2 = cross(meshData.Vertices[index + numSubdivisions + 2].Position - meshData.Vertices[index].Position,
					meshData.Vertices[index + 1].Position - meshData.Vertices[index].Position);
				vec3 n3 = cross(meshData.Vertices[index +  1].Position - meshData.Vertices[index].Position,
					meshData.Vertices[index - numSubdivisions - 1].Position - meshData.Vertices[index].Position);
				vec3 n4 = cross(meshData.Vertices[index - numSubdivisions - 1].Position - meshData.Vertices[index].Position,
					meshData.Vertices[index - numSubdivisions - 2].Position - meshData.Vertices[index].Position);
				vec3 n5 = cross(meshData.Vertices[index - numSubdivisions - 2].Position - meshData.Vertices[index].Position,
					meshData.Vertices[index - 1].Position - meshData.Vertices[index].Position);
				vec3 n6 = cross(meshData.Vertices[index - 1].Position - meshData.Vertices[index].Position,
					meshData.Vertices[index + numSubdivisions + 1].Position - meshData.Vertices[index].Position);
				meshData.Vertices[index].Normal = normalize(n1 + n2 + n3 + n4 + n5 + n6);
			}
		}
	}
	meshData.CalcTangent();
	return meshData;
}

MeshData GeometryGenerator::CreatePlane(float length, float width, uint32 numSubdivisions)
{
	MeshData meshData;
	float dl = length / numSubdivisions;
	float dw = length / numSubdivisions;
	float dt = 1 / (float)numSubdivisions;
	for (unsigned i = 0; i <=numSubdivisions; i++)
	{
		for (unsigned j = 0; j <=numSubdivisions; j++)
		{
			Vertex tmp = Vertex(vec3(i * dl - length * 0.5, 0, j * dw - width * 0.5), vec3(0, 1, 0), vec3(1, 0, 0), vec2(i * dt, j * dt));
			meshData.Vertices.push_back(tmp);
		}
	}
	for (unsigned i = 0; i < numSubdivisions; i++)
	{
		for (unsigned j = 0; j < numSubdivisions; j++)
		{
			int index = i * (numSubdivisions + 1) + j;
			meshData.Indices.push_back(index);
			meshData.Indices.push_back(index + numSubdivisions + 1);
			meshData.Indices.push_back(index + numSubdivisions + 2);

			meshData.Indices.push_back(index);
			meshData.Indices.push_back(index + 1);
			meshData.Indices.push_back(index + (numSubdivisions + 2));
		}
	}
	meshData.CalcTangent();
	return meshData;
}


void GeometryGenerator::Subdivide(MeshData& meshData)
{
	// Save a copy of the input geometry.
	MeshData inputCopy = meshData;


	meshData.Vertices.resize(0);
	meshData.Indices.resize(0);

	//       v1
	//       *
	//      / \
	//     /   \
	//  m0*-----*m1
	//   / \   / \
	//  /   \ /   \
	// *-----*-----*
	// v0    m2     v2

	GLuint numTris = (GLuint)inputCopy.Indices.size() / 3;
	for (GLuint i = 0; i < numTris; ++i)
	{
		Vertex v0 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 0]];
		Vertex v1 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 1]];
		Vertex v2 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 2]];

		//
		// Generate the midpoints.
		//

		Vertex m0 = MidPoint(v0, v1);
		Vertex m1 = MidPoint(v1, v2);
		Vertex m2 = MidPoint(v0, v2);

		//
		// Add new geometry.
		//

		meshData.Vertices.push_back(v0); // 0
		meshData.Vertices.push_back(v1); // 1
		meshData.Vertices.push_back(v2); // 2
		meshData.Vertices.push_back(m0); // 3
		meshData.Vertices.push_back(m1); // 4
		meshData.Vertices.push_back(m2); // 5

		meshData.Indices.push_back(i * 6 + 0);
		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 5);

		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 4);
		meshData.Indices.push_back(i * 6 + 5);

		meshData.Indices.push_back(i * 6 + 5);
		meshData.Indices.push_back(i * 6 + 4);
		meshData.Indices.push_back(i * 6 + 2);

		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 1);
		meshData.Indices.push_back(i * 6 + 4);
	}
}

Vertex GeometryGenerator::MidPoint(const Vertex& v0, const Vertex& v1)
{
	Vertex v;
	v.Normal =(v0.Normal + v1.Normal) ;
	v.Position = (v0.Position + v1.Position);
	v.TexCoord = (v0.TexCoord + v1.TexCoord);
	v.Normal *= 0.5;
	v.Position *= 0.5;
	v.TexCoord *= 0.5;
	return v;
}
float GeometryGenerator::random(vec2 st)
{
		return fract(sin(dot(st, vec2(12.9898, 78.233))) * 43758.5453123);
}
vec2 GeometryGenerator::random2(vec2 st)
{
	st = vec2(dot(st, vec2(127.1, 311.7)),
		dot(st, vec2(269.5, 183.3)));
	vec2 ttt= vec2(-1.0) + vec2(2.0) * fract(sin(st) * vec2(43758.5453123));
	vec2 aaaa = fract(sin(st) * vec2(43758.5453123));
	return vec2(-1.0) + vec2(2.0) * fract(sin(st) * vec2(43758.5453123));
}
float GeometryGenerator::ValueNoise(vec2 st)
{
	vec2 i = floor(st);
	vec2 f = fract(st);
	vec2 u = f * f * (vec2(3) - vec2(2) * f);
	float a = random(i);
	float b = random(i + vec2(1, 0));
	float c = random(i + vec2(0, 1));
	float d = random(i + vec2(1, 1));
	return mix(mix(a, b, u.x), mix(c, d, u.x), u.y);
}
float GeometryGenerator::GradientNoise(vec2 st)
{
	vec2 i = floor(st);
	vec2 f = fract(st);

	vec2 u = f * f * (vec2(3.0) - vec2(2.0) * f);
	return mix(mix(dot(random2(i + vec2(0.0, 0.0)), f - vec2(0.0, 0.0)),
		dot(random2(i + vec2(1.0, 0.0)), f - vec2(1.0, 0.0)), u.x),
		mix(dot(random2(i + vec2(0.0, 1.0)), f - vec2(0.0, 1.0)),
			dot(random2(i + vec2(1.0, 1.0)), f - vec2(1.0, 1.0)), u.x), u.y);
}
float GeometryGenerator::fbm(vec2 st, int octaves, float lacunarity, float gain, uint32 numSubdivisions, float amplitude, float frequency)
{
	float y = 0;
	for (int i = 0; i < octaves; i++) {
		vec2 tmp = frequency * st;
		y += amplitude * GradientNoise(frequency * st);
		frequency *= lacunarity;
		amplitude *= gain;
	}
	return y;
}
MeshData GeometryGenerator::CreateCylinder(float bottomRadius, float topRadius, float height, GLuint sliceCount, GLuint stackCount)
{
	MeshData meshData;

	//
	// Build Stacks.
	// 

	float stackHeight = height / stackCount;

	// Amount to increment radius as we move up each stack level from bottom to top.
	float radiusStep = (topRadius - bottomRadius) / stackCount;

	GLuint ringCount = stackCount + 1;

	// Compute vertices for each stack ring starting at the bottom and moving up.
	for (GLuint i = 0; i < ringCount; ++i)
	{
		float y = -0.5f * height + i * stackHeight;
		float r = bottomRadius + i * radiusStep;

		// vertices of ring
		float dTheta = 2.0f * (float)PI / sliceCount;
		for (GLuint j = 0; j <= sliceCount; ++j)
		{
			Vertex vertex;

			float c = cosf(j * dTheta);
			float s = sinf(j * dTheta);

			vertex.Position = vec3(r * c, y, r * s);

			vertex.TexCoord.x = (float)j / sliceCount;
			vertex.TexCoord.y = 1.0f - (float)i / stackCount;

			// Cylinder can be parameterized as follows, where we introduce v
			// parameter that goes in the same direction as the v tex-coord
			// so that the bitangent goes in the same direction as the v tex-coord.
			//   Let r0 be the bottom radius and let r1 be the top radius.
			//   y(v) = h - hv for v in [0,1].
			//   r(v) = r1 + (r0-r1)v
			//
			//   x(t, v) = r(v)*cos(t)
			//   y(t, v) = h - hv
			//   z(t, v) = r(v)*sin(t)
			// 
			//  dx/dt = -r(v)*sin(t)
			//  dy/dt = 0
			//  dz/dt = +r(v)*cos(t)
			//
			//  dx/dv = (r0-r1)*cos(t)
			//  dy/dv = -h
			//  dz/dv = (r0-r1)*sin(t)

			// This is unit length.

			float dr = bottomRadius - topRadius;
			vec3 T = vec3(dr * c, -height, dr * s);
			vec3 B = normalize(cross(vec3(r * c , 0, r * s),vec3(0,1,0)));
			vertex.Normal = normalize(cross(B,T));
			meshData.Vertices.push_back(vertex);
		}
	}

	// Add one because we duplicate the first and last vertex per ring
	// since the texture coordinates are different.
	GLuint ringVerTexCoordount = sliceCount + 1;

	// Compute indices for each stack.
	for (GLuint i = 0; i < stackCount; ++i)
	{
		for (GLuint j = 0; j < sliceCount; ++j)
		{
			meshData.Indices.push_back(i * ringVerTexCoordount + j);
			meshData.Indices.push_back((i + 1) * ringVerTexCoordount + j);
			meshData.Indices.push_back((i + 1) * ringVerTexCoordount + j + 1);

			meshData.Indices.push_back(i * ringVerTexCoordount + j);
			meshData.Indices.push_back((i + 1) * ringVerTexCoordount + j + 1);
			meshData.Indices.push_back(i * ringVerTexCoordount + j + 1);
		}
	}

	BuildCylinderTopCap(bottomRadius, topRadius, height, sliceCount, stackCount, meshData);
	BuildCylinderBottomCap(bottomRadius, topRadius, height, sliceCount, stackCount, meshData);

	return meshData;
}

void GeometryGenerator::BuildCylinderTopCap(float bottomRadius, float topRadius, float height,
	GLuint sliceCount, GLuint stackCount, MeshData& meshData)
{
	GLuint baseIndex = (GLuint)meshData.Vertices.size();

	float y = 0.5f * height;
	float dTheta = 2.0f * (float)PI / sliceCount;

	// Duplicate cap ring vertices because the texture coordinates and normals differ.
	for (GLuint i = 0; i <= sliceCount; ++i)
	{
		float x = topRadius * cosf(i * dTheta);
		float z = topRadius * sinf(i * dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		meshData.Vertices.push_back(Vertex(x, y, z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v));
	}

	// Cap center vertex.
	meshData.Vertices.push_back(Vertex(0.0f, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f));

	// Index of center vertex.
	GLuint centerIndex = (GLuint)meshData.Vertices.size() - 1;

	for (GLuint i = 0; i < sliceCount; ++i)
	{
		meshData.Indices.push_back(centerIndex);
		meshData.Indices.push_back(baseIndex + i + 1);
		meshData.Indices.push_back(baseIndex + i);
	}
}

void GeometryGenerator::BuildCylinderBottomCap(float bottomRadius, float topRadius, float height,
	GLuint sliceCount, GLuint stackCount, MeshData& meshData)
{
	// 
	// Build bottom cap.
	//

	GLuint baseIndex = (GLuint)meshData.Vertices.size();
	float y = -0.5f * height;

	// vertices of ring
	float dTheta = 2.0f * (float)PI / sliceCount;
	for (GLuint i = 0; i <= sliceCount; ++i)
	{
		float x = bottomRadius * cosf(i * dTheta);
		float z = bottomRadius * sinf(i * dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x / height + 0.5f;
		float v = z / height + 0.5f;
		meshData.Vertices.push_back(Vertex(x, y, z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v));
	}

	// Cap center vertex.
	meshData.Vertices.push_back(Vertex(0.0f, y, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f));

	// Cache the index of center vertex.
	GLuint centerIndex = (GLuint)meshData.Vertices.size() - 1;

	for (GLuint i = 0; i < sliceCount; ++i)
	{
		meshData.Indices.push_back(centerIndex);
		meshData.Indices.push_back(baseIndex + i);
		meshData.Indices.push_back(baseIndex + i + 1);
	}
}
