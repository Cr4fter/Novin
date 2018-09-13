#pragma once
#pragma region Internal Includes 
#pragma endregion //Internal Includes
#pragma region External Includes
#pragma endregion //External Includes

namespace NV
{
	namespace IRendering
	{
		enum class EShaderType
		{
			Vertex, 
			Fragment, 
			Compute
		};
		enum class EShaderLang
		{
			GLSL, 
			HLSL
		};
		enum class EShaderFormat
		{
			Default = 0, 
		};
	}
}