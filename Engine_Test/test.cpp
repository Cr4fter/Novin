#include "pch.h"
#include "BaseFunctions.h"
#include "ResourceLoader.h"
#include "ResourceManager.h"


TEST(BaseFunctions, ReadFileSizeCheck) {
	std::vector<char> buffer = NV::Base::ReadFile("../Demoproject//shaders//frag.spv", std::ios::binary);
	
	EXPECT_NE(buffer.size(), 0);
}

TEST(BaseFunctions, GetExtensionOfFileCheck)
{
	std::string str = NV::Base::GetExtensionOfFile("test.x.obj"); 
	std::string checkStr = "obj";
	EXPECT_STREQ(str.c_str(), checkStr.c_str());
}

TEST(ResourceLoader, LoadCheck)
{
	NV::Resources::ResourceLoader resLoader;

	const aiScene* objScene = new aiScene();
	objScene = resLoader.LoadMesh("../Demoproject//models//Boat.obj");
	EXPECT_TRUE(objScene->HasMeshes());
	

	const aiScene* fbxScene = new aiScene();
	fbxScene = resLoader.LoadMesh("../Demoproject//models//metal_kiste.FBX");
	EXPECT_TRUE(fbxScene->HasMeshes());

	NV::IRendering::RawTexData data = resLoader.LoadTexture("../Demoproject//textures//default.jpg");
	EXPECT_TRUE(data.Pixels != nullptr);

}

TEST(ResourceManager, StoreCheck)
{
	NV::Resources::ResourceManager* resManager = new NV::Resources::ResourceManager("../Demoproject");
	resManager->Init();
	const aiScene* scene = new aiScene();
	scene = resManager->GetScene(1);
	EXPECT_TRUE(scene != nullptr);

}