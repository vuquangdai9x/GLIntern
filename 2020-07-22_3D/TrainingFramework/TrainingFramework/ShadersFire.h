#pragma once
#include "Shaders.h"
class ShadersFire : public Shaders {
public:
	GLint m_u_textureLocation;
	GLint m_u_displTexLocation;
	GLint m_u_alphaMaskTexLocation;
	GLint m_u_timeLocation;
	GLint m_u_displMaxLocation;

	ShadersFire(int id);
	bool Init(char* fileVertexShader, char* fileFragmentShader);
};