#pragma once
#include "DirectX11.h"
class OceanManager
{
public:
	OceanManager(DirectX11& directx11, UINT texture_width, UINT  texture_height,
		float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor,
	bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, unsigned int sqrt_number_of_patchs);
	~OceanManager();
public:
	void Initialize();
	void Renderer();
private:
	VertexBuffer vtx_buffer_;
	IndexBuffer idx_buffer_;
	DirectX11& directx11_;
	float time_;

	UINT texture_width_;
	UINT texture_height_;
	float min_distance_;
	float max_distance_;
	float min_log2tessfactor_;
	float max_log2tessfactor_;
	bool draw_wires_;
	bool draw_normal_;
	bool apply_anglecorrection_;
	bool hold_;
	
	float size_terrain_;
	unsigned int sqrt_number_of_patchs_;
};