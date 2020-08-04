#pragma once
#include "Material.h"
#include "Texture.h"
class MaterialTerrain : public Material {
private:
	Texture *m_blendTexture, *m_texture1, *m_texture2, *m_texture3, *m_heightmap;
	float m_heightmapScaleFactor;

	GLint m_u_blendtexLocation;
	GLint m_u_Tex1Location;
	GLint m_u_Tex2Location;
	GLint m_u_Tex3Location;
	GLint m_u_heightmapLocation;
	GLint m_u_heightmapScaleFactorLocation;
public:
	MaterialTerrain(int id);
	bool Init(int iShaderId, int iBlendTextureId, int iTexture1Id, int iTexture2Id, int iTexture3Id);
	bool AddHeightmap(int iHeightmapId, float heightmapScaleFactor);
	void PrepareShader(Matrix & WVP);
};