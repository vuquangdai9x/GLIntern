#pragma once
#include "stdafx.h"

class Shaders 
{
public:
	Shaders(int id);
public:
	int m_id;
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint m_a_positionLocation;
	GLint m_a_normalLocation;
	GLint m_a_binormalLocation;
	GLint m_a_tangentLocation;
	GLint m_a_uvLocation;
	GLint m_a_colorLocation;
	GLint m_u_wvpLocation;

	GLint m_u_fogStartLocation, m_u_fogLengthLocation, m_u_fogColor;

	virtual bool Init(char * fileVertexShader, char * fileFragmentShader);
	virtual ~Shaders();
};