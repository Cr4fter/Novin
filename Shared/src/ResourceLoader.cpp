#include "ResourceLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

NV::Resources::ResourceLoader::ResourceLoader()
{
}

void NV::Resources::ResourceLoader::LoadShader(const std::string & shaderPath)
{
	std::vector<char> shader = NV::Base::ReadFile(shaderPath);
}

const aiScene* NV::Resources::ResourceLoader::LoadMesh(const std::string & objPath)
{
	Assimp::Importer importer;
	const aiScene* scene = new aiScene();
	scene = importer.ReadFile(objPath, 0);
	if (!scene)
	{
		//Broken file
	}
	return scene;
}

NV::IRendering::RawTexData NV::Resources::ResourceLoader::LoadTexture(const std::string & texPath)
{
	NV::IRendering::RawTexData texData = {};
	texData.Pixels = stbi_load(texPath.c_str(), &texData.Width, &texData.Height, &texData.TexChannels, 0);
	return texData;
}
