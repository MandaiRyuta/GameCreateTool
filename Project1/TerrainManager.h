#pragma once
#include "DirectX11.h"

class TerrainManager
{
public:
	TerrainManager(DirectX11& directx11);
	~TerrainManager();
public:
	void initialize(unsigned int div_x, unsigned int div_y, float frequency, float height, float size_x, float size_y);
	void Renderer();
private:
	VertexBuffer vtx_buffer_;
	IndexBuffer idx_buffer_;
	DirectX11& directx11_;
	float height_;
	float frequency_;
};