#include "stdafx.h"
#include "ShadersFire.h"

ShadersFire::ShadersFire(int id) : Shaders(id)
{
}

bool ShadersFire::Init(char* fileVertexShader, char* fileFragmentShader)
{
	if (!Shaders::Init(fileVertexShader, fileFragmentShader)) {
		return false;
	}
	m_u_textureLocation = glGetUniformLocation(program, "u_texture");
	m_u_displTexLocation = glGetUniformLocation(program, "u_displTex");
	m_u_alphaMaskTexLocation = glGetUniformLocation(program, "u_alphaMaskTex");
	m_u_timeLocation = glGetUniformLocation(program, "u_time");
	m_u_displMaxLocation = glGetUniformLocation(program, "u_displMax");
	return true;
}