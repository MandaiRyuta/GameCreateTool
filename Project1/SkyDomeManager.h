#pragma once
#include "DirectX11.h"

class SkyDomeManager
{
public:
	SkyDomeManager(DirectX11& directx11);
	~SkyDomeManager();
public:
	void initialize();
	void Renderer();
	void Cube(const math::float3 & size);
	void Cylinder(const float & height, const float & diameter, const unsigned int  & tessellation);
	void Sphere(const float & diameter, const unsigned int & tessellation);
	void ReverseWinding(IndexCollection & indices, VertexCollection & vertices);
	DirectX::XMVECTOR GetCircleVector(unsigned int i, unsigned int tessellation);
	void CreateCylinderCap(IndexCollection & idx_collection, VertexCollection & vtx_collection, const unsigned int & tessellation, const float & height, const float & radius, bool istop);
private:
	DirectX11& directx11_;
};