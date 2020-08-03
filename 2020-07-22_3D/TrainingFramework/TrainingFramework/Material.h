#pragma once
#include "../Utilities/utilities.h"

class Material {
protected:
	int m_id;
public:
	Material(int id);
	int GetId();
	virtual void PrepareShader(Matrix & m_WVP) = 0;
};