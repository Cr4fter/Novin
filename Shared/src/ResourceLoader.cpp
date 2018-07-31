#include "ResourceLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

NV::Resources::ResourceLoader::ResourceLoader()
{
}

void NV::Resources::ResourceLoader::LoadShader(const std::string & shaderPath, const std::string& ext)
{
	std::string fileName = NV::Base::GetFileName(shaderPath);

	std::vector<char> shader = NV::Base::ReadFile(shaderPath);
	if (shader.empty())
	{
		//TODO: Broken file
		return;
	}
	for (NV::IRendering::ShaderPack pack : m_shaderPacks)
	{
		if (pack.ShaderName == fileName)
		{
			IncludeShaderInPack(pack, shader, ext);
			return;
		}
	}
	NV::IRendering::ShaderPack newPack; 
	IncludeShaderInPack(newPack, shader, ext);
}


const aiScene* NV::Resources::ResourceLoader::LoadMesh(const std::string & objPath)
{
	Assimp::Importer importer;
	const aiScene* scene = new aiScene();
	scene = importer.ReadFile(objPath, 0);
	if (!scene)
	{
		//TODO: Broken file
	}
	return scene;
}

NV::IRendering::RawTexData NV::Resources::ResourceLoader::LoadTexture(const std::string & texPath)
{
	NV::IRendering::RawTexData texData = {};
	texData.Pixels = stbi_load(texPath.c_str(), &texData.Width, &texData.Height, &texData.TexChannels, 0);
	return texData;
}

void NV::Resources::ResourceLoader::IncludeShaderInPack(NV::IRendering::ShaderPack & pack, std::vector<char> shader, const std::string& ext)
{
	if (ext == "vert")
	{
		pack.VertexShader = shader;
	}
	if (ext == "frag")
	{
		pack.FragmentShader = shader;
	}
}
