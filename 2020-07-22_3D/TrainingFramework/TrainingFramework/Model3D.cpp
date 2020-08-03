#include "stdafx.h"
#include "Model3D.h"
#include <stddef.h>

Model3D::Model3D(int id) : m_id(id){}

Model3D::~Model3D()
{
	glDeleteBuffers(1, &m_vboId);
	glDeleteBuffers(1, &m_iboId);
}

bool Model3D::LoadFromFile(char* filePath, char* heightMapFile, float heightMapScale) {
	FILE * fIn = fopen(filePath, "r");
	if (fIn == NULL) {
		return false;
	}

	fscanf(fIn, "NrVertices: %d\n", &m_iNumOfVertex);
	//printf("Num of vertices: %d\n", m_iNumOfVertex);

	Vertex * aVertex = new Vertex[m_iNumOfVertex];
	float x, y, z, u, v, alpha;
	int index;
	unsigned int color;
	for (int i = 0; i < m_iNumOfVertex; i++) {
		fscanf(fIn, " %d. pos:[%f, %f, %f]; ", &index, &x, &y, &z);
		aVertex[i].SetPosition(x, y, z);
		fscanf(fIn, "norm:[%f, %f, %f]; ", &x, &y, &z);
		aVertex[i].SetNorm(x, y, z);
		fscanf(fIn, "binorm:[%f, %f, %f]; ", &x, &y, &z);
		aVertex[i].SetBinorm(x, y, z);
		fscanf(fIn, "tgt:[%f, %f, %f]; ", &x, &y, &z);
		aVertex[i].SetTangent(x, y, z);
		fscanf(fIn, "uv:[%f, %f];\n", &u, &v);
		aVertex[i].SetUV(u,v);

		//printf("Vertex %d:\n", index);
		//aVertex[i].PrintInfo();
	}

	fscanf(fIn, "NrIndices: %d\n", &m_iNumOfIndice);
	//printf("Num of indices: %d\n", m_iNumOfIndice);
	int v1, v2, v3;
	int * aIndice = new int[m_iNumOfIndice];
	for (int i = 0; i < m_iNumOfIndice/3; i++) {
		//0.    0, 1, 2
		fscanf(fIn, "   %d.    %d,    %d,    %d", &index, &v1, &v2, &v3);
		aIndice[3 * i] = v1;
		aIndice[3 * i + 1] = v2;
		aIndice[3 * i + 2] = v3;
		//printf("Indice %d: %d %d %d\n", i, v1, v2, v3);
	}


	if (heightMapFile != NULL) {
		int iWidth, iHeight, bpp;
		char *imageData = LoadTGA(heightMapFile, &iWidth, &iHeight, &bpp);
		if (imageData != NULL) {
			Vector3 color;
			int imgX, imgY;
			for (int i = 0; i < m_iNumOfVertex; i++) {
				imgX = aVertex[i].uv.x * iWidth;
				imgY = aVertex[i].uv.y * iHeight;
				
				color.x = (unsigned char)imageData[(imgY * iWidth + imgX)*(bpp / 8) + 0] / (float)255;
				color.y = (unsigned char)imageData[(imgY * iWidth + imgX)*(bpp / 8) + 1] / (float)255;
				color.z = (unsigned char)imageData[(imgY * iWidth + imgX)*(bpp / 8) + 2] / (float)255;
				float h = ((0.3 * color.x) + (0.59 * color.y) + (0.11 * color.z));
				aVertex[i].pos.y += heightMapScale * h;
			}
		}
		delete[] imageData;
	}


	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_iNumOfVertex, aVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_iNumOfIndice, aIndice, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// clear memory
	delete[] aVertex;
	delete[] aIndice;
	fclose(fIn);

	return true;
}

