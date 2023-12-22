#pragma once

#include "glad/glad.h"

#include <vector>

namespace Endeavor
{
	struct GLElementBuffer
	{
	public:
		GLElementBuffer() = default;
		~GLElementBuffer();

		void Init();

		void Bind();
		void Unbind();

		void Push(uint32_t index);
		void Flush();

		void BufferData();
		uint64_t GetIndexCount() { return m_NumIndices;  }

	private:
		uint32_t m_ID = 0;
		uint64_t m_NumIndices = 0;
		std::vector<uint32_t> m_Indices;
	};
}