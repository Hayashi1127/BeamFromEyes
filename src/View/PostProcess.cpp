# pragma once

# include "./View/PostProcess.hpp"

namespace BeamForEyes::View
{
	void PostProcess::Process(const MSRenderTexture renderTexture)
	{
		// ポストプロセス?
		{
			const ScopedCustomShader2D shader{ psBright };
			const ScopedRenderTarget2D target{ gaussianA4->clear(ColorF{ 0.0 }) };
			renderTexture.scaled(0.25).draw();
		}

		Shader::GaussianBlur(*gaussianA4, *gaussianB4, *gaussianA4);

		Shader::Downsample(*gaussianA4, *gaussianA8);
		Shader::GaussianBlur(*gaussianA8, *gaussianB8, *gaussianA8);
		Shader::GaussianBlur(*gaussianA8, *gaussianB8, *gaussianA8);

		const ScopedRenderStates2D blend{ BlendState::AdditiveRGB };
		{
			const ScopedRenderTarget2D target{ *gaussianA4 };
			gaussianA8->scaled(3.0).draw(ColorF{ 3.0 });
		}

		gaussianA4->resized(*windowSizePtr).draw(ColorF{ 1.0 });
	}

	PostProcess::PostProcess(const Size* size)
	{
		windowSizePtr = size;
		gaussianA4 = new RenderTexture(*windowSizePtr / 4);
		gaussianB4 = new RenderTexture(*windowSizePtr / 4);
		gaussianA8 = new RenderTexture(*windowSizePtr / 8);
		gaussianB8 = new RenderTexture(*windowSizePtr / 8);
	}

	PostProcess::~PostProcess()
	{

	}
}
