#ifndef _BASE_FUNCTIONS_H_
#error Do not include this file directly!
#elif !defined _BASE_FUNCTIONS_HPP_
#define _BASE_FUNCTIONS_HPP_

std::vector<char> NV::Base::ReadFile(const std::string & filePath, const int& mode)
{
	std::ifstream file(filePath, std::ios::ate | mode);
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

#endif // _BASIC_FUNCTIONS_H