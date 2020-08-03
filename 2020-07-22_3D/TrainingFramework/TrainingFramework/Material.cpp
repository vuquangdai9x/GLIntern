#include "stdafx.h"
#include "Material.h"
#include "ResourceManager.h"

Material::Material(int id)
{
	m_id = id;
}

int Material::GetId()
{
	return m_id;
}
