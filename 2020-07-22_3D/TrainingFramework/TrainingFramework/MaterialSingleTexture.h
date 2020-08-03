#pragma once
#include "Material.h"
#include "Texture.h"
#include "ShadersSingleTex.h"
class MaterialSingleTexture : public Material {
private:
	Texture* m_texture;
	ShadersSingleTex * m_shader;
public:
	MaterialSingleTexture(int id);
	bool Init(int iShaderId, int iTextureId);
	void PrepareShader(Matrix & m_WVP);
};