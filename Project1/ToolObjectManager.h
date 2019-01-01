#pragma once
#include "DirectX11.h"

class ToolObjectManager
{
public:
	ToolObjectManager(DirectX11& directx11);
	~ToolObjectManager();
public:
	void initialize(unsigned int div_x, unsigned int div_y, float size_x, float size_y);
	void Renderer();
private:
	VertexBuffer vtx_buffer_;
	IndexBuffer idx_buffer_;
	DirectX11& directx11_;
};