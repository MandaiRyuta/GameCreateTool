#include "SkyDomeManager.h"

void SkyDomeManager::Cube(const math::float3& size)
{
	IndexCollection idx_collection;
	VertexCollection vtx_collection;

	const int FaceCount = 6;
	const int UVCount = 4;
	static const DirectX::XMVECTORF32 faceNormals[FaceCount] =
	{
		{ { { 0, 0, 1, 0 } } },
		{ { { 0, 0,-1, 0 } } },
		{ { { 1, 0, 0, 0 } } },
		{ { { -1, 0, 0, 0 } } },
		{ { { 0, 1, 0, 0 } } },
		{ { { 0,-1, 0, 0 } } },
	};

	static const DirectX::XMVECTORF32 uv_s[UVCount] =
	{
		{ { { 1, 0, 0, 0 } } },
		{ { { 1, 1, 0, 0 } } },
		{ { { 0, 1, 0, 0 } } },
		{ { { 0, 0, 0, 0 } } },
	};

	DirectX::XMVECTOR tsize = DirectX::XMLoadFloat3(&size);
	tsize = DirectX::XMVectorDivide(tsize, DirectX::g_XMTwo);

	for (int i = 0; i < FaceCount; i++)
	{
		DirectX::XMVECTOR normal = faceNormals[i];

		DirectX::XMVECTOR basis = (i >= 4) ? DirectX::g_XMIdentityR2 : DirectX::g_XMIdentityR1;

		DirectX::XMVECTOR side1 = DirectX::XMVector3Cross(normal, basis);
		DirectX::XMVECTOR side2 = DirectX::XMVector3Cross(normal, side1);

		unsigned int vbase = static_cast<unsigned int>(vtx_collection.size());

		idx_collection.emplace_back(vbase + 0);
		idx_collection.emplace_back(vbase + 1);
		idx_collection.emplace_back(vbase + 2);

		idx_collection.emplace_back(vbase + 0);
		idx_collection.emplace_back(vbase + 2);
		idx_collection.emplace_back(vbase + 3);

		// Four vertices per face.
		// (normal - side1 - side2) * tsize // normal // t0
		vtx_collection.emplace_back(DirectX::XMVectorMultiply(DirectX::XMVectorSubtract(DirectX::XMVectorSubtract(normal, side1), side2), tsize));

		// (normal - side1 + side2) * tsize // normal // t1
		vtx_collection.emplace_back(DirectX::XMVectorMultiply(DirectX::XMVectorAdd(DirectX::XMVectorSubtract(normal, side1), side2), tsize));

		// (normal + side1 + side2) * tsize // normal // t2
		vtx_collection.emplace_back(DirectX::XMVectorMultiply(DirectX::XMVectorAdd(normal, DirectX::XMVectorAdd(side1, side2)), tsize));

		// (normal + side1 - side2) * tsize // normal // t3
		vtx_collection.emplace_back(DirectX::XMVectorMultiply(DirectX::XMVectorSubtract(DirectX::XMVectorAdd(normal, side1), side2), tsize));
	}

	ReverseWinding(idx_collection, vtx_collection);

	directx11_.createMesh(MeshID::Default, idx_collection, vtx_collection, Topology::TriangleList);
	directx11_.createShader(ShaderID::Default, "shapechange.hlsl");
}

void SkyDomeManager::Cylinder(const float & height, const float & diameter, const unsigned int & tessellation)
{
	IndexCollection idx_collection;
	VertexCollection vtx_collection;

	float cylinder_height = height / 2;

	DirectX::XMVECTOR top_offset = DirectX::XMVectorScale(DirectX::g_XMIdentityR1, height);

	float radius = diameter / 2;
	unsigned int stride = tessellation + 1;

	for (unsigned int i = 0; i <= tessellation; i++)
	{
		DirectX::XMVECTOR normal = GetCircleVector(i, tessellation);

		DirectX::XMVECTOR side_offset = DirectX::XMVectorScale(normal, radius);

		float u = float(i) / tessellation;

		vtx_collection.emplace_back(DirectX::XMVectorAdd(side_offset, top_offset));
		vtx_collection.emplace_back(DirectX::XMVectorSubtract(side_offset, top_offset));

		idx_collection.emplace_back(i * 2);
		idx_collection.emplace_back((i * 2 + 2) % (stride * 2));
		idx_collection.emplace_back(i * 2 + 1);

		idx_collection.emplace_back(i * 2 + 1);
		idx_collection.emplace_back((i * 2 + 2) % (stride * 2));
		idx_collection.emplace_back((i * 2 + 3) % (stride * 2));
	}

	CreateCylinderCap(idx_collection, vtx_collection, tessellation, height, radius, true);
	CreateCylinderCap(idx_collection, vtx_collection, tessellation, height, radius, false);

	ReverseWinding(idx_collection, vtx_collection);

	directx11_.createMesh(MeshID::Default, idx_collection, vtx_collection, Topology::TriangleList);
	directx11_.createShader(ShaderID::Default, "shapechange.hlsl");
}

void SkyDomeManager::Sphere(const float & diameter, const unsigned int & tessellation)
{
	IndexCollection idx_collection;
	VertexCollection vtx_collection;

	unsigned int verticalSegments = tessellation;
	unsigned int horizontalSegment = tessellation * 2;

	float radius = diameter / 2;

	for (unsigned int i = 0; i <= verticalSegments; i++)
	{
		float v = 1 - float(i) / verticalSegments;
		
		float latitude = (i * DirectX::XM_PI / verticalSegments) - DirectX::XM_PIDIV2;

		float dy, dxz;

		DirectX::XMScalarSinCos(&dy, &dxz, latitude);

		for (unsigned int j = 0; j <= horizontalSegment; j++)
		{
			float u = float(j) / horizontalSegment;
			
			float longitude = j * DirectX::XM_2PI / horizontalSegment;
			float dx, dz;

			DirectX::XMScalarSinCos(&dx, &dz, longitude);

			dx *= dxz;
			dz *= dxz;

			DirectX::XMVECTOR normal = DirectX::XMVectorSet(dx, dy, dz, 0);

			vtx_collection.push_back(DirectX::XMVectorScale(normal, radius));
		}
	}

	unsigned int stride = horizontalSegment + 1;

	for (unsigned int i = 0; i < verticalSegments; i++)
	{
		for (unsigned int j = 0; j <= horizontalSegment; j++)
		{
			unsigned int nextI = i + 1;
			unsigned int nextJ = (j + 1) % stride;

			idx_collection.emplace_back(i * stride + j);
			idx_collection.emplace_back(nextI * stride + j);
			idx_collection.emplace_back(i * stride + nextJ);

			idx_collection.emplace_back(i * stride + nextJ);
			idx_collection.emplace_back(nextI * stride + j);
			idx_collection.emplace_back(nextI * stride + nextJ);
		}
	}

	ReverseWinding(idx_collection, vtx_collection);

	directx11_.createMesh(MeshID::Default, idx_collection, vtx_collection, Topology::TriangleList);
	directx11_.createShader(ShaderID::Default, "shapechange.hlsl");
}

void SkyDomeManager::ReverseWinding(IndexCollection & indices, VertexCollection & vertices)
{
	for (auto it = indices.begin(); it != indices.end(); it += 3)
	{
		std::swap(*it, *(it + 2));
	}
}

DirectX::XMVECTOR SkyDomeManager::GetCircleVector(unsigned int i, unsigned int tessellation)
{
	float angle = i * DirectX::XM_2PI / tessellation;
	float dx, dz;

	DirectX::XMScalarSinCos(&dx, &dz, angle);

	DirectX::XMVECTORF32 v = { {{ dx, 0, dz, 0 }} };

	return v;
}

void SkyDomeManager::CreateCylinderCap(IndexCollection & idx_collection, VertexCollection & vtx_collection, const unsigned int & tessellation, const float & height, const float & radius, bool istop)
{
	for (unsigned int i = 0; i < tessellation - 2; i++)
	{
		unsigned int i1 = (i + 1) % tessellation;
		unsigned int i2 = (i + 2) % tessellation;

		if (istop)
		{
			std::swap(i1, i2);
		}

		unsigned int vbase = vtx_collection.size();

		idx_collection.emplace_back(vbase);
		idx_collection.emplace_back(vbase + i1);
		idx_collection.emplace_back(vbase + i2);
	}

	DirectX::XMVECTOR normal = DirectX::g_XMIdentityR1;

	if (!istop)
	{
		normal = DirectX::XMVectorNegate(normal);
	}

	for (unsigned int i = 0; i < tessellation; i++)
	{
		DirectX::XMVECTOR circle_vector = GetCircleVector(i, tessellation);
		DirectX::XMVECTOR position = DirectX::XMVectorAdd(DirectX::XMVectorScale(circle_vector, radius), DirectX::XMVectorScale(normal, height));
		
		vtx_collection.emplace_back(position);
	}
}

SkyDomeManager::SkyDomeManager(DirectX11 & directx11)
	: directx11_(directx11)
{
}

SkyDomeManager::~SkyDomeManager()
{
}

void SkyDomeManager::initialize()
{
	//Cylinder(10.0f, 10.0f, 20);
	//Sphere(10.0f, 15);
	Cube({ 10.0f,10.0f,10.0f });
}

void SkyDomeManager::Renderer()
{
	static float p = 0.0f;
	math::matrix world = math::matrix::CreateRotationX(p);

	directx11_.setWorld(world);
	directx11_.setShader(0, ShaderID::Default);
	directx11_.updatePerMeshConstantBuffer();
	directx11_.setMesh(MeshID::Default);

	p += 0.004f;
}
