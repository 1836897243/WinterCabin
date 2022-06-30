#include "VAO.h"
#include "LoadShaders.h"

void VAO::Rotate(mat4 R)
{
	MR = MR * R;
	Model = MT * MR * MS;
}

void VAO::Scale(mat4 S)
{
	MS = MS * S;
	Model = MT * MR * MS;
}

void VAO::Tranlate(mat4 T)
{
	MT = MT * T;
	Model = MT * MR * MS;
}

void VAO::Init(bool isDepth, GLuint shaderProgram)
{
	
	glUseProgram(shaderProgram);
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, meshData.Vertices.size()*sizeof(Vertex), &meshData.Vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(Position);
	glVertexAttribPointer(Normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3)));
	glEnableVertexAttribArray(Normal);
	if (Mtl.MtlKind)
	{
		glVertexAttribPointer(Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(vec3)));
		glEnableVertexAttribArray(Tangent);
		glVertexAttribPointer(TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(vec3)));
		glEnableVertexAttribArray(TexCoord);
	}
	glGenBuffers(1, &EboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.Indices.size() * sizeof(unsigned int), &meshData.Indices[0], GL_STATIC_DRAW);
	if (!isDepth)
	{
		if (Mtl.MtlKind & Material::MapKa)
		{
			glGenTextures(1, &MapKaId);
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, MapKaId);
			TextureData Data(Mtl.getMapKa(),true);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Data.w, Data.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data.data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		if (Mtl.MtlKind & Material::MapKd)
		{
			glGenTextures(1, &MapKdId);
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, MapKdId);
			TextureData Data(Mtl.getMapKd(), true);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Data.w, Data.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data.data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		if (Mtl.MtlKind & Material::MapKs)
		{
			glGenTextures(1, &MapKsId);
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, MapKsId);
			TextureData Data(Mtl.getMapKs(), true);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Data.w, Data.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data.data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		if (Mtl.MtlKind & Material::MapBump)
		{
			glGenTextures(1, &MapBumpId);
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, MapBumpId);
			TextureData Data(Mtl.getMapBump(), true);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Data.w, Data.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data.data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		if (Mtl.MtlKind & Material::MapNs)
		{
			glGenTextures(1, &MapNsId);
			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, MapNsId);
			TextureData Data(Mtl.getMapNs(), true);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Data.w, Data.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data.data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	
	
}
void VAO::updateUniform(GLuint shaderProgram)
{
	glUseProgram(shaderProgram);
	GLint loc;
	if (Mtl.MtlKind & Material::MapKa)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, MapKaId);
		loc = glGetUniformLocation(shaderProgram, "map_Ka");
		assert(loc >= 0);
		glUniform1i(loc, 1);
	}
	else
	{
		loc = glGetUniformLocation(shaderProgram, "Ka");
		assert(loc >= 0);
		vec3 Ambient = Mtl.Ka;
		glUniform3f(loc, Ambient[0], Ambient[1], Ambient[2]);
	}
	if (Mtl.MtlKind & Material::MapKd)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, MapKdId);
		loc = glGetUniformLocation(shaderProgram, "map_Kd");
		assert(loc >= 0);
		glUniform1i(loc, 2);
	}
	else
	{
		loc = glGetUniformLocation(shaderProgram, "Kd");
		assert(loc >= 0);
		vec3 Diffuse = Mtl.Kd;
		glUniform3f(loc, Diffuse[0], Diffuse[1], Diffuse[2]);
	}
	if (Mtl.MtlKind & Material::MapKs)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, MapKsId);
		loc = glGetUniformLocation(shaderProgram, "map_Ks");
		assert(loc >= 0);
		glUniform1i(loc, 3);
	}
	else
	{
		loc = glGetUniformLocation(shaderProgram, "Ks");
		assert(loc >= 0);
		vec3 Specular = Mtl.Ks;
		glUniform3f(loc, Specular[0], Specular[1], Specular[2]);
	}
	if (Mtl.MtlKind & Material::MapNs)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, MapNsId);
		loc = glGetUniformLocation(shaderProgram, "map_Ns");
		assert(loc >= 0);
		glUniform1i(loc, 4);
	}
	else
	{
		loc = glGetUniformLocation(shaderProgram, "Ns");
		assert(loc >= 0);
		float Ns = Mtl.Ns;
		glUniform1f(loc, Ns);
	}
	if (Mtl.MtlKind & Material::MapBump)
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, MapBumpId);
		loc = glGetUniformLocation(shaderProgram, "map_Bump");
		assert(loc >= 0);
		glUniform1i(loc, 5);
	}
	loc = glGetUniformLocation(shaderProgram, "MtlKind");
	assert(loc >= 0);
	glUniform1i(loc, Mtl.MtlKind);
}
void VAO::Draw(GLuint shaderProgram)
{
	glUseProgram(shaderProgram);
	GLint loc = glGetUniformLocation(shaderProgram, "Model");
	assert(loc >= 0);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &Model[0][0]);
	glBindVertexArray(VaoId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glDrawElements(GL_TRIANGLES, meshData.Indices.size(), GL_UNSIGNED_INT, nullptr);
}
