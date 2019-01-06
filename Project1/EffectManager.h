#pragma once
#include "DirectX11.h"

#define MAX_NUM (500)

class EffectManager
{
public:
	EffectManager(DirectX11& directx11);
	~EffectManager();

public:
	void Initialize();
	void Renderer();
private:
	VertexBuffer vtx_buffer;
	IndexBuffer idx_buffer;
	DirectX11& directx11_;
	float time_;
	math::matrix ins[MAX_NUM];
};