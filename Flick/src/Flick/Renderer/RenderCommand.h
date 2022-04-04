#pragma once

#include "RendererAPI.h"

namespace Flick
{
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& va, uint32_t count = 0)
		{
			s_RendererAPI->DrawIndexed(va, count);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}