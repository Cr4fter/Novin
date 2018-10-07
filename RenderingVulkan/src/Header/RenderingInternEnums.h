#pragma once

namespace NV
{
	namespace Rendering
	{
		enum EShaderType
		{
			ENone = 0, //Use this to force deleting all existing shaders in the pack
			EVertex = (1 << 0),
			EFragment = (1 << 1)
		};
	}
}