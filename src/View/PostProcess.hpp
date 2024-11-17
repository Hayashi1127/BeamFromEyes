# pragma once

# include <Siv3D.hpp>

namespace BeamForEyes::View
{
	class PostProcess
	{
	private:
		const Size* windowSizePtr;

		// ブルーム用テクスチャ
		const RenderTexture* gaussianA4;
		const RenderTexture* gaussianB4;
		const RenderTexture* gaussianA8;
		const RenderTexture* gaussianB8;

		const PixelShader psBright = HLSL{ U"example/shader/hlsl/extract_bright_linear.hlsl", U"PS" }
		| GLSL{ U"example/shader/glsl/extract_bright_linear.frag", {{U"PSConstants2D", 0}} };
	public :
		PostProcess(const Size* size);
		~PostProcess();

		void Process(const MSRenderTexture renderTexture);
	};
}
