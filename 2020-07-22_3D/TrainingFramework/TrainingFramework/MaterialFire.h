#pragma once
#include "Material.h"
#include "Texture.h"
#include "ShadersFire.h"
class MaterialFire : public Material {
private:
	Texture* m_texture, * m_displTexture, * m_alphaMaskTexture;
	float m_displMax, m_timeScale;
	ShadersFire* m_shader;
public:
	MaterialFire(int id);
	bool Init(int iShaderId, int iTextureId, int iDisplTextureId, int iAlphaMaskTexture2Id, float displMax, float timeScale);
	void PrepareShader(Matrix& m_WVP);
};