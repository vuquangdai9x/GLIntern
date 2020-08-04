#pragma once
#include "Material.h"
#include "Texture.h"
class MaterialSingleTexture : public Material {
private:
	Texture* m_texture;
	GLint m_u_textureLocation;
public:
	MaterialSingleTexture(int id);
	bool Init(int iShaderId, int iTextureId);
	void PrepareShader(Matrix & WVP);
};