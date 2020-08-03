#include "stdafx.h"
#include "Shaders.h"

Shaders::Shaders(int id) : m_id(id) {}

bool Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return false;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return false;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	m_a_positionLocation = glGetAttribLocation(program, "a_posL");
	//colorAttribute = glGetAttribLocation(program, "a_color");
	m_a_normalLocation = glGetAttribLocation(program, "a_normal");
	m_a_binormalLocation = glGetAttribLocation(program, "a_binormal");
	m_a_tangentLocation = glGetAttribLocation(program, "a_tangent");
	m_a_uvLocation = glGetAttribLocation(program, "a_uv");
	m_u_wvpLocation = glGetUniformLocation(program, "u_wvp");

	m_u_fogStartLocation = glGetUniformLocation(program, "u_fogStart");
	m_u_fogLengthLocation = glGetUniformLocation(program, "u_fogLength");
	m_u_fogColor = glGetUniformLocation(program, "u_fogColor");

	return true;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}