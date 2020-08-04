#pragma once
#include "Material.h"
#include "Texture.h"
class MaterialFire : public Material {
private:
	Texture* m_texture, * m_displTexture, * m_alphaMaskTexture;
	float m_displMax, m_timeScale;

	GLint m_u_textureLocation;
	GLint m_u_displTexLocation;
	GLint m_u_alphaMaskTexLocation;
	GLint m_u_timeLocation;
	GLint m_u_displMaxLocation;
public:
	MaterialFire(int id);
	bool Init(int iShaderId, int iTextureId, int iDisplTextureId, int iAlphaMaskTexture2Id, float displMax, float timeScale);
	void PrepareShader(Matrix& WVP);
};