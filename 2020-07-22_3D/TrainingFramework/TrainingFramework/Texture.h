#pragma once
#include "../Utilities/utilities.h"

class Texture {
protected:
	int m_id;
	GLuint m_textureHandle;
	bool m_isCubeTexture;
public:
	Texture(int id, bool isCubeTexture);
	virtual ~Texture();

	enum TILING_MODE
	{
		CLAMP, REPEAT, MIRROR
	};

	GLuint GetTextureHandle();
	bool IsCubeTexture();
	bool LoadTextureFromFile(char* filePath, TILING_MODE tilingMode);
	bool LoadCubeTextureFromFile(char* filePath, TILING_MODE tilingMode);
	bool LoadCubeTextureFromSplittedFiles(char ** imageFiles, TILING_MODE tilingMode);
	int GetId() { return m_id; }
};