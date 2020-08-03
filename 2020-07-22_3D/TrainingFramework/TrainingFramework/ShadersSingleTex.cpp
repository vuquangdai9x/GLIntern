#include "stdafx.h"
#include "ShadersSingleTex.h"

ShadersSingleTex::ShadersSingleTex(int id) : Shaders(id)
{
}

bool ShadersSingleTex::Init(char * fileVertexShader, char * fileFragmentShader)
{
	if (!Shaders::Init(fileVertexShader, fileFragmentShader)) {
		return false;
	}
	m_u_textureLocation = glGetUniformLocation(program, "u_texture");
	return true;
}