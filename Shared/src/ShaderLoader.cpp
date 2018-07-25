#include "ShaderLoader.h"

bool NV::Tools::ShaderLoader::LoadFile(std::string & filePath)
{
	std::vector<char> buffer = NV::Base::ReadFile(filePath, std::ios::binary);

	return true;
}
