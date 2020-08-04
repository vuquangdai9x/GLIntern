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
	isLoadSuccessfully = Material::Init(iShaderId);
	if (!isLoadSuccessfully) return false;

	m_u_textureLocation = glGetUniformLocation(m_shader->program, "u_texture");
	m_u_displTexLocation = glGetUniformLocation(m_shader->program, "u_displTex");
	m_u_alphaMaskTexLocation = glGetUniformLocation(m_shader->program, "u_alphaMaskTex");
	m_u_timeLocation = glGetUniformLocation(m_shader->program, "u_time");
	m_u_displMaxLocation = glGetUniformLocation(m_shader->program, "u_displMax");

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

void MaterialFire::PrepareShader(Matrix & WVP)
{
	Material::PrepareShader(WVP);

	glUseProgram(m_shader->program);
	if (m_u_textureLocation != -1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureHandle());
		glUniform1i(m_u_textureLocation, 0);
	}
	if (m_u_displTexLocation != -1) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_displTexture->GetTextureHandle());
		glUniform1i(m_u_displTexLocation, 1);
	}
	if (m_u_alphaMaskTexLocation != -1) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_alphaMaskTexture->GetTextureHandle());
		glUniform1i(m_u_alphaMaskTexLocation, 2);
	}
	if (m_u_displMaxLocation != -1) {
		glUniform1f(m_u_displMaxLocation, (GLfloat)m_displMax);
	}
	if (m_u_timeLocation != -1) {
		glUniform1f(m_u_timeLocation, (GLfloat)(SceneManager::GetInstance()->m_time * m_timeScale));
	}
}
