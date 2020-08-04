#pragma once
#include "../Utilities/utilities.h"
#include "Shaders.h"

class Material {
protected:
	int m_id;
	Shaders* m_shader;

	GLint m_a_positionLocation;
	GLint m_a_normalLocation;
	GLint m_a_binormalLocation;
	GLint m_a_tangentLocation;
	GLint m_a_uvLocation;
	GLint m_a_colorLocation;
	GLint m_u_wvpLocation;
	GLint m_u_fogStartLocation, m_u_fogLengthLocation, m_u_fogColor;
public:
	Material(int id);
	int GetId();
	virtual bool Init(int iShaderId);
	virtual void PrepareShader(Matrix & WVP);
};