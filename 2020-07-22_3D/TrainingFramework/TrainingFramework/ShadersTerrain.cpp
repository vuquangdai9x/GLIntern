#include "stdafx.h"
#include "ShadersTerrain.h"

ShadersTerrain::ShadersTerrain(int id) : Shaders(id)
{
}

bool ShadersTerrain::Init(char * fileVertexShader, char * fileFragmentShader)
{
	if (!Shaders::Init(fileVertexShader, fileFragmentShader)) {
		return false;
	}
	m_u_blendtexLocation = glGetUniformLocation(program, "u_texture[0]");
	m_u_Tex1Location = glGetUniformLocation(program, "u_texture[1]");
	m_u_Tex2Location = glGetUniformLocation(program, "u_texture[2]");
	m_u_Tex3Location = glGetUniformLocation(program, "u_texture[3]");
	m_u_heightmapLocation = glGetUniformLocation(program, "u_heightmap");
	m_u_heightmapScaleFactorLocation = glGetUniformLocation(program, "u_heightmapScaleFactor");
	return true;
}
