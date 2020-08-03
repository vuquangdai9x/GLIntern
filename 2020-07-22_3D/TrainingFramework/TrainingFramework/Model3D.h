#pragma once
#include "stdafx.h"
#include "Vertex.h"
#include "Shaders.h"
#include "../Utilities/utilities.h"

class Model3D {
public:
	Model3D(int id);
	~Model3D();
public:
	int m_id;
	GLuint m_vboId, m_iboId;
	int m_iNumOfVertex, m_iNumOfIndice;

	bool LoadFromFile(char* filePath, char* heightMapFile = NULL, float heightMapScale = 1);
};