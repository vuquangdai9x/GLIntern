#include "stdafx.h"
#include "MaterialSingleTexture.h"
#include "ResourceManager.h"
#include "Globals.h"

MaterialSingleTexture::MaterialSingleTexture(int id) : Material(id)
{
}

bool MaterialSingleTexture::Init(int iShaderId, int iTextureId)
{
	bool isLoadSuccessful = true;
	isLoadSuccessful = Material::Init(iShaderId);
	if (!isLoadSuccessful) return false;

	m_u_textureLocation = glGetUniformLocation(m_shader->program, "u_texture");

	m_texture = ResourceManager::GetInstance()->GetTexture(iTextureId);
	if (m_texture == NULL) {
		printf("[ERR] Material Single Texture: Failed to get texture %d\n", iTextureId);
		isLoadSuccessful = false;
	}
	return isLoadSuccessful;
}

void MaterialSingleTexture::PrepareShader(Matrix & WVP)
{
	Material::PrepareShader(WVP);

	glUseProgram(m_shader->program);
	if (m_u_textureLocation != -1) {
		if (m_texture->IsCubeTexture()) {
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture->GetTextureHandle());
		}
		else {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureHandle());
		}
		glUniform1i(m_u_textureLocation, 0);
	}
}
