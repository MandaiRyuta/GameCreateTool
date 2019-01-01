#include "SeaManager.h"
#include "GlobalFunction.h"

SeaManager::SeaManager(DirectX11 & directx11)
	:	directx11_(directx11)
	, time_(0.0f)
{
}

SeaManager::~SeaManager()
{
}

void SeaManager::initialize(unsigned int div_x, unsigned int div_y, float size_x, float size_y)
{
	VertexCollection vtx_collection_;
	IndexCollection idx_collection_;

	float w = size_x / div_x, h = size_y / div_y;

	for (unsigned int n = 0; n < div_y + 1; ++n)
	{
		for (unsigned int i = 0; i < div_x + 1; ++i)
		{
			vtx_collection_.emplace_back(DirectX::XMFLOAT3(-w * div_x * 0.5f + i * w, 0, -h * div_y * 0.5f + n * h));
		}
	}

	for (unsigned int n = 0; n < div_y; ++n)
	{
		for (unsigned int i = 0; i < div_x; ++i)
		{
			idx_collection_.emplace_back(v2to1(i + 0, n + 0, div_x));
			idx_collection_.emplace_back(v2to1(i + 0, n + 0, div_x));
			idx_collection_.emplace_back(v2to1(i + 1, n + 0, div_x));
			idx_collection_.emplace_back(v2to1(i + 0, n + 1, div_x));
			idx_collection_.emplace_back(v2to1(i + 1, n + 1, div_x));
			idx_collection_.emplace_back(v2to1(i + 1, n + 1, div_x));
		}
	}

	directx11_.createMesh(MeshID::Default, idx_collection_, vtx_collection_, Topology::TriangleStrip);
	directx11_.createShader(ShaderID::Default, "sea.hlsl");
}

void SeaManager::Renderer()
{
	auto kpos01 = directx11_.getShaderVariable<math::float2>(ShaderID::Default, "kpos01");
	auto kpos02 = directx11_.getShaderVariable<math::float2>(ShaderID::Default, "kpos02");
	auto wlen = directx11_.getShaderVariable<math::float2>(ShaderID::Default, "wlen");
	auto amp = directx11_.getShaderVariable<math::float2>(ShaderID::Default, "amp");
	auto freq = directx11_.getShaderVariable<float>(ShaderID::Default, "freq");
	auto time = directx11_.getShaderVariable<float>(ShaderID::Default, "time");

	*kpos01 = math::float2(1.0f,1.0f);
	*kpos02 = math::float2(1.0f, 0.0f);
	*wlen = { 4.0f, 4.0f };
	*amp = { 0.75f,0.423f };
	*freq = 3.141592f;
	*time = time_;

	directx11_.setShader(0, ShaderID::Default);
	directx11_.updatePerMeshConstantBuffer();
	directx11_.updateConstantBuffer(ShaderID::Default);
	directx11_.setMesh(MeshID::Default);

	time_ += 0.01f;
}
