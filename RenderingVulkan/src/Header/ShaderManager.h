#pragma once
#pragma region Internal Includes 
#include "RendererStorage.h"
#include "BaseFunctions.h"
#pragma endregion //Internal Includes
#pragma region External Includes
#include <string>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw3native.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan/vulkan_win32.h"
#include "vulkan/libspirv.h"
#include "Public/ShaderLang.h"
#include "Include/ResourceLimits.h"
#include "ResourceLimits.h"
#include "SPIRV/GlslangToSpv.h"
#include "GlobalStructs.h"
#include <iostream>
#pragma endregion //External Includes

namespace NV
{
	namespace Rendering
	{
		class ShaderManager
		{
		public:
			using NVUShader = std::shared_ptr<glslang::TShader>;

			using UProgramPtr = std::shared_ptr<glslang::TProgram>;
		private:

			const std::string m_defaultVert = { 
				"#version 450 																		 \n\
				#extension GL_ARB_separate_shader_objects : enable 									 \n\
																									 \n\
				layout(binding = 0) uniform UniformBufferObject { 									 \n\
				mat4 model;		 																	 \n\
				mat4 view;		 																	 \n\
				mat4 proj;		 																	 \n\
			} ubo;																					 \n\
																									 \n\
			layout(location = 0) in vec3 inPosition;												 \n\
			layout(location = 1) in vec3 inColor;													 \n\
			layout(location = 2) in vec2 inTexCoord;												 \n\
			layout(location = 3) in vec3 inNormal;													 \n\
																									 \n\
			layout(location = 0) out vec3 fragColor;												 \n\
			layout(location = 1) out vec2 fragTexCoord;												 \n\
			layout(location = 2) out vec3 fragNormal;												 \n\
			layout(location = 3) out vec3 lightDirection;											 \n\
																									 \n\
			out gl_PerVertex{																		 \n\
				vec4 gl_Position;																	 \n\
			};																						 \n\
																									 \n\
			void main() {																			 \n\
				gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);				 \n\
																									 \n\
				vec3 inPositionWS = (ubo.model*vec4(inPosition,1)).xyz;								 \n\
																									 \n\
				vec3 inPositionCS = (ubo.view*ubo.model*vec4(inPosition,1)).xyz;					 \n\
				vec3 viewDirCS = vec3(0,0,0) - inPositionCS;										 \n\
																									 \n\
				vec3 lightPosCS = (ubo.view*vec4(100,50,-50,1)).xyz;								 \n\
																									 \n\
																									 \n\
				lightDirection = normalize(lightPosCS + viewDirCS);									 \n\
				fragNormal = normalize(ubo.view*ubo.model*vec4(inNormal,0)).xyz;					 \n\
																									 \n\
				fragColor = inColor;																 \n\
				fragTexCoord = inTexCoord;															 \n\
																									 \n\
			}"																						  
		};
			const std::string m_defaultFrag = { 
				"#version 450																				  \n\
				#extension GL_ARB_separate_shader_objects : enable											  \n\
																											  \n\
				layout(binding = 1) uniform sampler2D texSampler;											  \n\
			layout(binding = 2) uniform sampler2D normalSampler;											  \n\
																											  \n\
			layout(location = 0) in vec3 fragColor;															  \n\
			layout(location = 1) in vec2 fragTexCoord;														  \n\
			layout(location = 2) in vec3 fragNormal;														  \n\
			layout(location = 3) in vec3 lightDirection;													  \n\
																											  \n\
			layout(location = 0) out vec4 outColor;															  \n\
																											  \n\
			void main() {																					  \n\
				vec4 lightColor = vec4(1,1,1,1);															  \n\
				vec4 baseColor = texture(texSampler, fragTexCoord);											  \n\
				vec4 normal = texture(normalSampler, fragTexCoord);											  \n\
				float lightPower = 5;																		  \n\
				float cosTheta = clamp(dot(normalize(fragNormal),normalize(lightDirection)), 0, 1);			  \n\
				vec4 matDiffCol = baseColor * cosTheta*lightColor*lightPower;								  \n\
																											  \n\
				vec4 matAmbCol = 0.1 *baseColor;															  \n\
																											  \n\
				vec3 E = normalize(lightDirection);															  \n\
				vec3 R = reflect(-lightDirection, fragNormal);												  \n\
				float cosAlpha = clamp(dot(E,R), 0, 1);														  \n\
																											  \n\
				vec4 matSpecCol = lightColor * lightPower* pow(cosAlpha, 60);								  \n\
				outColor = matDiffCol + matAmbCol + normal;													  \n\
			}"
			};
			const int m_defaultVersion = 110;
			const std::string m_vertEntry = "VertMain";
			const std::string m_fragEntry = "FragMain";

			const TBuiltInResource m_defaultRes = glslang::DefaultTBuiltInResource;
			const EShMessages m_defaultMsg = EShMsgDefault;

			VkDevice m_logicalDevice;

			RendererStorage* m_storage;
		public:
			ShaderManager(RendererStorage* storage);

			void Init();

			uint32_t SetNewShader(UProgramPtr program, NV::IRendering::ShaderPack& pack);

			const char* GetVertEntry() const; 

			const char* GetFragEntry() const;

			void Release();

			~ShaderManager();

		private: 
			void CreateDefaultShader();

			void SetupShader(NVUShader& shader, const char* const* strings, const uint32_t& numStrings, const glslang::EShSource& srcLang, const EShLanguage& shaderType);
							   
			void ParseShader(NVUShader& shader, const TBuiltInResource& resource, const EShMessages& msg);

			uint32_t CreateShaderModule(UProgramPtr program);
		};
	}
}