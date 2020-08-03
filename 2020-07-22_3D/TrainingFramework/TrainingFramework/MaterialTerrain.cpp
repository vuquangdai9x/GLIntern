#include "stdafx.h"
#include "MaterialTerrain.h"
#include "ShadersSingleTex.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Globals.h"

MaterialTerrain::MaterialTerrain(int id) : Material(id)
{
}

bool MaterialTerrain::Init(int iShaderId, int iBlendTextureId, int iTexture1Id, int iTexture2Id, int iTexture3Id)
{
	bool isLoadSuccessfully = true;
	m_shader = dynamic_cast<ShadersTerrain*>(ResourceManager::GetInstance()->GetShader(iShaderId));
	if (m_shader == NULL) {
		if (m_shader == NULL) printf("[ERR] Material: Failed to get shader %d\n", iShaderId);
		isLoadSuccessfully = false;
	}
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

void MaterialTerrain::PrepareShader(Matrix & m_WVP)
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

	if (m_shader->m_u_blendtexLocation != -1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_blendTexture->GetTextureHandle());
		glUniform1i(m_shader->m_u_blendtexLocation, 0);
	}
	if (m_shader->m_u_Tex1Location != -1) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture1->GetTextureHandle());
		glUniform1i(m_shader->m_u_Tex1Location, 1);
	}
	if (m_shader->m_u_Tex2Location != -1) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_texture2->GetTextureHandle());
		glUniform1i(m_shader->m_u_Tex2Location, 2);
	}
	if (m_shader->m_u_Tex3Location != -1) {
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, m_texture3->GetTextureHandle());
		glUniform1i(m_shader->m_u_Tex3Location, 3);
	}
	if (m_shader->m_u_heightmapLocation != -1 && m_shader->m_u_heightmapScaleFactorLocation != -1) {
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, m_heightmap->GetTextureHandle());
		glUniform1i(m_shader->m_u_heightmapLocation, 4);
		glUniform1f(m_shader->m_u_heightmapScaleFactorLocation, (GLfloat)m_heightmapScaleFactor);
	}

	// fog
	if (m_shader->m_u_fogStartLocation != -1 && m_shader->m_u_fogLengthLocation != -1 && m_shader->m_u_fogColor != -1) {
		glUniform1f(m_shader->m_u_fogStartLocation, SceneManager::GetInstance()->m_fogStart);
		glUniform1f(m_shader->m_u_fogLengthLocation, SceneManager::GetInstance()->m_fogLength);
		glUniform4fv(m_shader->m_u_fogColor, 1, (GLfloat*) &(SceneManager::GetInstance()->m_fogColor));
		//Vector4 color = SceneManager::GetInstance()->m_fogColor;
		//glUniform4f(m_shader->m_u_fogColor, color.x, color.y, color.z, color.w);
	}
}
