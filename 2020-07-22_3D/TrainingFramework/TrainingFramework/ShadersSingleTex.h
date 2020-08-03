#pragma once
#include "Shaders.h"
class ShadersSingleTex : public Shaders {
public:
	GLint m_u_textureLocation;
	ShadersSingleTex(int id);
	bool Init(char * fileVertexShader, char * fileFragmentShader);
};