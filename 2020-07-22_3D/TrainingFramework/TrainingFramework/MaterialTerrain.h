#pragma once
#include "Material.h"
#include "Texture.h"
#include "ShadersTerrain.h"
class MaterialTerrain : public Material {
private:
	Texture *m_blendTexture, *m_texture1, *m_texture2, *m_texture3, *m_heightmap;
	float m_heightmapScaleFactor;
	ShadersTerrain * m_shader;
public:
	MaterialTerrain(int id);
	bool Init(int iShaderId, int iBlendTextureId, int iTexture1Id, int iTexture2Id, int iTexture3Id);
	bool AddHeightmap(int iHeightmapId, float heightmapScaleFactor);
	void PrepareShader(Matrix & m_WVP);
};