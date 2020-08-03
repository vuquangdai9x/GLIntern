#include "stdafx.h"
#include "MaterialSingleTexture.h"
#include "ShadersSingleTex.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Globals.h"

MaterialSingleTexture::MaterialSingleTexture(int id) : Material(id)
{
}

bool MaterialSingleTexture::Init(int iShaderId, int iTextureId)
{
	bool isLoadSuccessful = true;
	m_shader = dynamic_cast<ShadersSingleTex*>(ResourceManager::GetInstance()->GetShader(iShaderId));
	if (m_shader == NULL) {
		if (m_shader == NULL) printf("[ERR] Material: Failed to get shader %d\n", iShaderId);
		isLoadSuccessful = false;
	}
	m_texture = ResourceManager::GetInstance()->GetTexture(iTextureId);
	if (m_texture == NULL) {
		printf("[ERR] Material Single Texture: Failed to get texture %d\n", iTextureId);
		isLoadSuccessful = false;
	}
	return isLoadSuccessful;
}

void MaterialSingleTexture::PrepareShader(Matrix & m_WVP)
{
	glUseProgram(m_shader->program);
	if (m_shader->m_a_positionLocation != -1)
	{
		//printf("pos ");
		glEnableVertexAttribArray(m_shader->m_a_positionLocation);
		glVertexAttribPointer(m_shader->m_a_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
	}
	if (m_shader->m_a_normalLocation != -1)
	{
		//printf("norm ");
		glEnableVertexAttribArray(m_shader->m_a_normalLocation);
		glVertexAttribPointer(m_shader->m_a_normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, norm));
	}
	if (m_shader->m_a_binormalLocation != -1)
	{
		//printf("binorm ");
		glEnableVertexAttribArray(m_shader->m_a_binormalLocation);
		glVertexAttribPointer(m_shader->m_a_binormalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, binorm));
	}
	if (m_shader->m_a_tangentLocation != -1)
	{
		//printf("tangent ");
		glEnableVertexAttribArray(m_shader->m_a_tangentLocation);
		glVertexAttribPointer(m_shader->m_a_tangentLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tangent));
	}
	if (m_shader->m_a_uvLocation != -1)
	{
		//printf("uv ");
		glEnableVertexAttribArray(m_shader->m_a_uvLocation);
		glVertexAttribPointer(m_shader->m_a_uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	}
	if (m_shader->m_u_wvpLocation != -1) {
		//printf("wvp ");
		glUniformMatrix4fv(m_shader->m_u_wvpLocation, 1, GL_FALSE, (GLfloat*)&m_WVP);
	}
	if (m_shader->m_u_textureLocation != -1) {
		if (m_texture->IsCubeTexture()) {
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture->GetTextureHandle());
		}
		else {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureHandle());
		}
		glUniform1i(m_shader->m_u_textureLocation, 0);
	}

	// fog
	if (m_shader->m_u_fogStartLocation != -1 && m_shader->m_u_fogLengthLocation != -1 && m_shader->m_u_fogColor != -1) {
		glUniform1f(m_shader->m_u_fogStartLocation, SceneManager::GetInstance()->m_fogStart);
		glUniform1f(m_shader->m_u_fogLengthLocation, SceneManager::GetInstance()->m_fogLength);
		glUniform4fv(m_shader->m_u_fogColor, 1, (GLfloat*) &(SceneManager::GetInstance()->m_fogColor));
	}
}
