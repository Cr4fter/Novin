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

TEST(BaseFunctions, GetFileNameCheck)
{
	std::string str = NV::Base::GetFileName("test.x.obj");
	std::string checkStr = "test"; 
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

NV::Resources::ResourceManager* resManager = new NV::Resources::ResourceManager("../Demoproject");

TEST(ResourceManager, StoreCheck)
{
	resManager->Init();
	const aiScene* scene = new aiScene();
	scene = resManager->GetScene(0);
	EXPECT_TRUE(scene);

	NV::IRendering::RawTexData texData = resManager->GetTexData(0);
	EXPECT_TRUE(texData.Pixels);
}

TEST(ResourceManager, RemoveCheck)
{
	resManager->RemoveScene(0);
	const aiScene* scene = resManager->GetScene(0);
	EXPECT_FALSE(scene);

	resManager->RemoveTexture(0);
	NV::IRendering::RawTexData texData = resManager->GetTexData(0);
	EXPECT_FALSE(texData.Pixels);

	delete resManager;
}
