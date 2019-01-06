#include "EffectManager.h"

EffectManager::EffectManager(DirectX11 & directx11)
	:directx11_(directx11)
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	time_ = 0.0f;

	VertexCollectionUV vtx_collection;
	IndexCollection idx_collection;

	vtx_collection.emplace_back(math::float3(-3.0f,-3.0f, 0.0f), math::float2(0.0f, 1.0f));
	vtx_collection.emplace_back(math::float3( 3.0f,-3.0f, 0.0f), math::float2(1.0f, 1.0f));
	vtx_collection.emplace_back(math::float3(-3.0f, 3.0f, 0.0f), math::float2(0.0f, 0.0f));
	vtx_collection.emplace_back(math::float3( 3.0f, 3.0f, 0.0f), math::float2(1.0f, 0.0f));

	idx_collection.emplace_back(0);
	idx_collection.emplace_back(2);
	idx_collection.emplace_back(1);
	idx_collection.emplace_back(3);

	directx11_.createTexture(TextureID::EffectParticle, "particle2.png");
	directx11_.createTextureMesh(MeshID::Default, idx_collection, vtx_collection, Topology::TriangleStrip);
	directx11_.createShader(ShaderID::Default, "EffectParticle.hlsl");
	directx11_.createBlend(BlendID::AlphaADD, BlendOption::Add, BlendType::SrcAlpha, BlendType::InvSrcAlpha, BlendOption::Add, BlendType::One, BlendType::Zero);
	//directx11_.createBlend(BlendID::AlphaINV, BlendOption::Add, BlendType::One, BlendType::InvSrcAlpha, BlendOption::Add, BlendType::One, BlendType::InvSrcAlpha);

}

void EffectManager::Renderer()
{

	auto time = directx11_.getShaderVariable<float>(ShaderID::Default, "time");
	auto InstanceWorld = directx11_.getShaderVariable<math::matrix*>(ShaderID::Default, "InstancingWorld");
	auto Life = directx11_.getShaderVariable<int*>(ShaderID::Default, "Life");
	for (unsigned int i = 0; i < MAX_NUM; i++)
	{
		math::float3 move;
		//move = DirectX::XMVectorHermite(math::float3(0.0f, 0.0f, 0.0f), math::float3(1.0f, -1.0f, 1.0f), math::float3(0.0f, -100.0f, 0.0f), math::float3(0.0f, 1.0f, -1.0f), time_);
		ins[i] = math::matrix::CreateTranslation(0.0f,0.0f,0.0f);
	}
	memcpy(InstanceWorld, ins, sizeof(math::matrix) * MAX_NUM);

	if (time_ >= 1.0f)
	{
		time_ = 0.0f;
	}

	*time = time_;

	directx11_.setShaderResourceFromTexture(0, { TextureID::EffectParticle });
	directx11_.setShader(0,ShaderID::Default);
	directx11_.updatePerMeshConstantBuffer();
	directx11_.updateConstantBuffer(ShaderID::Default);
	//directx11_.setBlend(BlendID::AlphaINV);
	directx11_.setBlend(BlendID::AlphaADD);
	directx11_.setMesh(MeshID::Default, MAX_NUM);

	time_ += 0.00001f;
}
