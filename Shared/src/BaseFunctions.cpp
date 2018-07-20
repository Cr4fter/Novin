#include "BaseFunctions.h"

std::vector<char> NV::Base::ReadFile(const std::string & filePath)
{
	std::ifstream file(filePath, std::ios::ate | std::ios::binary);
	if (!file.is_open()) {
		throw std::runtime_error("failed to open file");
		return std::vector<char>(0);
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}
