#pragma once
#include "Shaders.h"
class ShadersTerrain : public Shaders {
public:
	GLint m_u_blendtexLocation;
	GLint m_u_Tex1Location;
	GLint m_u_Tex2Location;
	GLint m_u_Tex3Location;
	GLint m_u_heightmapLocation;
	GLint m_u_heightmapScaleFactorLocation;
	ShadersTerrain(int id);
	bool Init(char * fileVertexShader, char * fileFragmentShader);
};