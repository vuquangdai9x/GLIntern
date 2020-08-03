#include "stdafx.h"
#include "MaterialFire.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Globals.h"

MaterialFire::MaterialFire(int id) : Material(id)
{
}

bool MaterialFire::Init(int iShaderId, int iTextureId, int iDisplTextureId, int iAlphaMaskTexture2Id, float displMax, float timeScale)
{
	bool isLoadSuccessfully = true;
	m_shader = dynamic_cast<ShadersFire*>(ResourceManager::GetInstance()->GetShader(iShaderId));
	if (m_shader == NULL) {
		if (m_shader == NULL) printf("[ERR] Material: Failed to get shader %d\n", iShaderId);
		isLoadSuccessfully = false;
	}
	m_texture = ResourceManager::GetInstance()->GetTexture(iTextureId);
	if (m_texture == NULL) {
		printf("[ERR] Material Single Texture: Failed to get texture %d\n", m_texture);
		isLoadSuccessfully = false;
	}
	m_displTexture = ResourceManager::GetInstance()->GetTexture(iDisplTextureId);
	if (m_displTexture == NULL) {
		printf("[ERR] Material Single Texture: Failed to get texture1 %d\n", iDisplTextureId);
		isLoadSuccessfully = false;
	}
	m_alphaMaskTexture = ResourceManager::GetInstance()->GetTexture(iAlphaMaskTexture2Id);
	if (m_alphaMaskTexture == NULL) {
		printf("[ERR] Material Single Texture: Failed to get texture2 %d\n", iAlphaMaskTexture2Id);
		isLoadSuccessfully = false;
	}
	m_displMax = displMax;
	m_timeScale = timeScale;
	return isLoadSuccessfully;
}

void MaterialFire::PrepareShader(Matrix & m_WVP)
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
		glUniformMatrix4fv(m_shader->m_u_wvpLocation, 1, GL_FALSE, (GLfloat*)& m_WVP);
	}

	if (m_shader->m_u_textureLocation != -1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureHandle());
		glUniform1i(m_shader->m_u_textureLocation, 0);
	}
	if (m_shader->m_u_displTexLocation != -1) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_displTexture->GetTextureHandle());
		glUniform1i(m_shader->m_u_displTexLocation, 1);
	}
	if (m_shader->m_u_alphaMaskTexLocation != -1) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_alphaMaskTexture->GetTextureHandle());
		glUniform1i(m_shader->m_u_alphaMaskTexLocation, 2);
	}
	if (m_shader->m_u_displMaxLocation != -1) {
		glUniform1f(m_shader->m_u_displMaxLocation, (GLfloat)m_displMax);
	}
	if (m_shader->m_u_timeLocation != -1) {
		glUniform1f(m_shader->m_u_timeLocation, (GLfloat)(SceneManager::GetInstance()->m_time * m_timeScale));
	}

	// fog
	if (m_shader->m_u_fogStartLocation != -1 && m_shader->m_u_fogLengthLocation != -1 && m_shader->m_u_fogColor != -1) {
		glUniform1f(m_shader->m_u_fogStartLocation, SceneManager::GetInstance()->m_fogStart);
		glUniform1f(m_shader->m_u_fogLengthLocation, SceneManager::GetInstance()->m_fogLength);
		glUniform4fv(m_shader->m_u_fogColor, 1, (GLfloat*) & (SceneManager::GetInstance()->m_fogColor));
		//Vector4 color = SceneManager::GetInstance()->m_fogColor;
		//glUniform4f(m_shader->m_u_fogColor, color.x, color.y, color.z, color.w);
	}
}
