#include "stdafx.h"
#include "MaterialTerrain.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Globals.h"

MaterialTerrain::MaterialTerrain(int id) : Material(id)
{
}

bool MaterialTerrain::Init(int iShaderId, int iBlendTextureId, int iTexture1Id, int iTexture2Id, int iTexture3Id)
{
	bool isLoadSuccessfully = true;
	isLoadSuccessfully = Material::Init(iShaderId);
	if (!isLoadSuccessfully) return false;

	m_u_blendtexLocation = glGetUniformLocation(m_shader->program, "u_texture[0]");
	m_u_Tex1Location = glGetUniformLocation(m_shader->program, "u_texture[1]");
	m_u_Tex2Location = glGetUniformLocation(m_shader->program, "u_texture[2]");
	m_u_Tex3Location = glGetUniformLocation(m_shader->program, "u_texture[3]");
	m_u_heightmapLocation = glGetUniformLocation(m_shader->program, "u_heightmap");
	m_u_heightmapScaleFactorLocation = glGetUniformLocation(m_shader->program, "u_heightmapScaleFactor");

	m_blendTexture = ResourceManager::GetInstance()->GetTexture(iBlendTextureId);
	if (m_blendTexture == NULL) {
		printf("[ERR] Material Single Texture: Failed to get blend texture %d\n", iBlendTextureId);
		isLoadSuccessfully = false;
	}
	m_texture1 = ResourceManager::GetInstance()->GetTexture(iTexture1Id);
	if (m_texture1 == NULL) {
		printf("[ERR] Material Single Texture: Failed to get texture1 %d\n", iTexture1Id);
		isLoadSuccessfully = false;
	}
	m_texture2 = ResourceManager::GetInstance()->GetTexture(iTexture2Id);
	if (m_texture2 == NULL) {
		printf("[ERR] Material Single Texture: Failed to get texture2 %d\n", iTexture2Id);
		isLoadSuccessfully = false;
	}
	m_texture3 = ResourceManager::GetInstance()->GetTexture(iTexture3Id);
	if (m_texture3 == NULL) {
		printf("[ERR] Material Single Texture: Failed to get texture3 %d\n", iTexture3Id);
		isLoadSuccessfully = false;
	}
	return isLoadSuccessfully;
}

bool MaterialTerrain::AddHeightmap(int iHeightmapId, float heightmapScaleFactor)
{
	m_heightmap = ResourceManager::GetInstance()->GetTexture(iHeightmapId);
	if (m_heightmap == NULL) {
		if (m_heightmap == NULL) printf("[ERR] Material: Failed to get shader %d\n", iHeightmapId);
		return false;
	}
	m_heightmapScaleFactor = heightmapScaleFactor;
	return true;
}

void MaterialTerrain::PrepareShader(Matrix & WVP)
{
	Material::PrepareShader(WVP);

	glUseProgram(m_shader->program);
	if (m_u_blendtexLocation != -1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_blendTexture->GetTextureHandle());
		glUniform1i(m_u_blendtexLocation, 0);
	}
	if (m_u_Tex1Location != -1) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture1->GetTextureHandle());
		glUniform1i(m_u_Tex1Location, 1);
	}
	if (m_u_Tex2Location != -1) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_texture2->GetTextureHandle());
		glUniform1i(m_u_Tex2Location, 2);
	}
	if (m_u_Tex3Location != -1) {
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, m_texture3->GetTextureHandle());
		glUniform1i(m_u_Tex3Location, 3);
	}
	if (m_u_heightmapLocation != -1 && m_u_heightmapScaleFactorLocation != -1) {
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, m_heightmap->GetTextureHandle());
		glUniform1i(m_u_heightmapLocation, 4);
		glUniform1f(m_u_heightmapScaleFactorLocation, (GLfloat)m_heightmapScaleFactor);
	}
}
