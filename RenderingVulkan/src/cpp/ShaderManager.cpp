#include "../Header/ShaderManager.h"

NV::Rendering::ShaderManager::ShaderManager(RendererStorage* storage)
	:m_logicalDevice(VK_NULL_HANDLE)
	,m_storage(storage)
{
}

void NV::Rendering::ShaderManager::Init()
{
	ShInitialize();
	m_logicalDevice = m_storage->GetLogicalDevice();
	CreateDefaultShader();
}

uint32_t NV::Rendering::ShaderManager::SetNewShader(UProgramPtr program, NV::IRendering::ShaderPack & pack)
{

	NVUShader vertShader(new glslang::TShader(EShLanguage::EShLangVertex));
	NVUShader fragShader(new glslang::TShader(EShLanguage::EShLangFragment));

	const char* const vertString[] = { pack.VertexShader.ShaderCode };
	const char* const fragString[] = { pack.FragShader.ShaderCode };

	SetupShader(vertShader, vertString, 1, glslang::EShSource::EShSourceGlsl, EShLanguage::EShLangVertex);
	SetupShader(fragShader, fragString, 1, glslang::EShSource::EShSourceGlsl, EShLanguage::EShLangFragment);

	ParseShader(vertShader, m_defaultRes, m_defaultMsg);
	ParseShader(fragShader, m_defaultRes, m_defaultMsg);

	program->addShader(vertShader.get());
	program->addShader(fragShader.get());

	

	if (!program->link(m_defaultMsg))
	{
#ifndef NDEBUG
		std::cerr << program->getInfoDebugLog();
#endif
		std::cerr << program->getInfoLog();
	}
	return CreateShaderModule(program);
}

const char * NV::Rendering::ShaderManager::GetVertEntry() const
{
	return m_vertEntry.data();
}

const char * NV::Rendering::ShaderManager::GetFragEntry() const
{
	return m_fragEntry.data();
}

void NV::Rendering::ShaderManager::SetupShader(NVUShader& shader, const char * const * strings, const uint32_t& numStrings, const glslang::EShSource& srcLang, const EShLanguage& shaderType)
{
	shader->setStrings(strings, numStrings);
	switch (shaderType)
	{
	case EShLanguage::EShLangVertex: 
		shader->setEntryPoint(m_vertEntry.data());
		shader->setSourceEntryPoint("main");
		break;
	case EShLanguage::EShLangFragment:
		shader->setEntryPoint(m_fragEntry.data());
		shader->setSourceEntryPoint("main");
		break;
	}
	shader->setEnvInput(srcLang, shaderType, glslang::EShClient::EShClientVulkan, m_defaultVersion);
	shader->setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetVulkan_1_1);
	shader->setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0);
}

void NV::Rendering::ShaderManager::ParseShader(NVUShader & shader, const TBuiltInResource & resource = glslang::DefaultTBuiltInResource, const EShMessages & msg = EShMsgDefault)
{
//	std::string str;
//	glslang::TShader::ForbidIncluder includer;
//	if (shader->preprocess(&m_defaultRes, m_defaultVersion, ENoProfile, false, false, msg, &str, includer))
//	{
//#ifndef NDEBUG
//		std::cerr << shader->getInfoDebugLog();
//#endif
//		std::cerr << shader->getInfoLog();
//
//	}

	//for (int r = 0; r < glslang::EResCount; ++r)
	//{
	//	const glslang::TResourceType res = glslang::TResourceType(r); 

	//	shader->setShiftBinding((res, )
	//}

	if (!shader->parse(&resource, m_defaultVersion, false, msg/*, includer*/))
	{
#ifndef NDEBUG
		std::cerr << shader->getInfoDebugLog();
#endif
		std::cerr << shader->getInfoLog();
	}
}

uint32_t NV::Rendering::ShaderManager::CreateShaderModule(UProgramPtr program)
{
	std::vector<uint32_t> vertSpv;
	std::vector<uint32_t> fragSpv;
	glslang::GlslangToSpv(*program->getIntermediate(EShLangVertex), vertSpv);
	glslang::GlslangToSpv(*program->getIntermediate(EShLangFragment), fragSpv);

	VkShaderModuleCreateInfo vertCreateInfo = {};
	vertCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	vertCreateInfo.codeSize = vertSpv.size();
	vertCreateInfo.pCode = vertSpv.data();

	VkShaderModuleCreateInfo fragCreateInfo = {};
	fragCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	fragCreateInfo.codeSize = fragSpv.size();
	fragCreateInfo.pCode = fragSpv.data();


	std::array<VkShaderModuleCreateInfo, 2> createInfos = { vertCreateInfo, fragCreateInfo };

	VkShaderModule shaderModule = VK_NULL_HANDLE;
	if (vkCreateShaderModule(m_logicalDevice, createInfos.data(), nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module");
	}
	return m_storage->StoreShader(shaderModule);
}

void NV::Rendering::ShaderManager::Release()
{
	ShFinalize();
}

NV::Rendering::ShaderManager::~ShaderManager()
{
}

void NV::Rendering::ShaderManager::CreateDefaultShader()
{
	/*std::vector<char> vertShader = NV::Base::ReadFile("../Demoproject/shaders//shader.vert");
	std::vector<char> fragShader = NV::Base::ReadFile("../Demoproject/shaders//shader.frag");

	UProgramPtr defaultProgram(new glslang::TProgram());
	NV::IRendering::ShaderPack defaultPack;
	defaultPack.VertexShader.ShaderCode = vertShader.data();
	defaultPack.VertexShader.Language = NV::IRendering::EShaderLang::GLSL;
	defaultPack.VertexShader.Type = NV::IRendering::EShaderType::Vertex;
	defaultPack.FragShader.ShaderCode = fragShader.data();
	defaultPack.FragShader.Language = NV::IRendering::EShaderLang::GLSL;
	defaultPack.FragShader.Type = NV::IRendering::EShaderType::Fragment;

	SetNewShader(defaultProgram, defaultPack);*/

	std::vector<char> vertcode = NV::Base::ReadFile("../Demoproject/shaders//shader.vert", std::iostream::in);
	std::vector<char> fragcode = NV::Base::ReadFile("../Demoproject/shaders//shader.frag", std::iostream::in);
	UProgramPtr vertprogram(new glslang::TProgram());
	UProgramPtr fragprogram(new glslang::TProgram());
	
	glslang::TShader* vertShader = new glslang::TShader(EShLanguage::EShLangVertex);
	glslang::TShader* fragShader = new glslang::TShader(EShLanguage::EShLangFragment);
	const char* const vertString[] = { vertcode.data() };
	const char* const fragString[] = { fragcode.data() };

	vertShader->setStrings(vertString, 1);
	vertShader->setEnvInput(glslang::EShSource::EShSourceGlsl, EShLanguage::EShLangVertex, glslang::EShClient::EShClientVulkan, m_defaultVersion);
	vertShader->setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetVulkan_1_1);
	vertShader->setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0);

	vertShader->parse(&glslang::DefaultTBuiltInResource, m_defaultVersion, false, EShMsgDefault);

	fragShader->setStrings(fragString, 1); 
	fragShader->setEnvInput(glslang::EShSource::EShSourceGlsl, EShLanguage::EShLangFragment, glslang::EShClient::EShClientVulkan, m_defaultVersion); 
	fragShader->setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetVulkan_1_1); 
	fragShader->setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0); 

	fragShader->parse(&glslang::DefaultTBuiltInResource, m_defaultVersion, false, EShMsgDefault); 

	vertprogram->addShader(vertShader);
	fragprogram->addShader(fragShader); 

	vertprogram->link(EShMsgDefault);
	fragprogram->link(EShMsgDefault); 

	std::vector<uint32_t> vertShaderSpv;
	glslang::GlslangToSpv(*vertprogram->getIntermediate(EShLangVertex), vertShaderSpv);

	std::vector<uint32_t> fragShaderSpv;
	glslang::GlslangToSpv(*fragprogram->getIntermediate(EShLangFragment), fragShaderSpv); 

	VkShaderModuleCreateInfo vertCreateInfo = {};
	vertCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	vertCreateInfo.codeSize = vertShaderSpv.size();
	vertCreateInfo.pCode = vertShaderSpv.data();

	VkShaderModuleCreateInfo fragCreateInfo = {};
	fragCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO; 
	fragCreateInfo.codeSize = fragShaderSpv.size(); 
	fragCreateInfo.pCode = fragShaderSpv.data(); 

	std::array<VkShaderModuleCreateInfo, 1> createInfos = {vertCreateInfo};
	VkShaderModule shaderModule = VK_NULL_HANDLE;
	if (vkCreateShaderModule(m_logicalDevice, createInfos.data(), nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module");
	}
	m_storage->StoreShader(shaderModule);
	std::array<VkShaderModuleCreateInfo, 1> createInfos2 = { fragCreateInfo }; 
	VkShaderModule shaderModule1 = VK_NULL_HANDLE; 
	if (vkCreateShaderModule(m_logicalDevice, createInfos2.data(), nullptr, &shaderModule1) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module1");
	}
	m_storage->StoreShader(shaderModule1);
}
