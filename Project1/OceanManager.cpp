#include "OceanManager.h"
#include "GlobalFunction.h"

OceanManager::OceanManager(DirectX11 & directx11)
	: directx11_(directx11)
{
}

OceanManager::~OceanManager()
{
}

void OceanManager::Initialize(UINT texture_width, UINT  texture_height,
	float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor,
	bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, unsigned int sqrt_number_of_patchs)
{
	texture_width_ = texture_width;
	texture_height_ = texture_height;
	time_ = time;
	min_distance_ = min_distance;
	max_distance_ = max_distance;
	min_log2tessfactor_ = min_log2tessfactor;
	max_log2tessfactor_ = max_log2tessfactor;
	draw_wires_ = draw_wires;
	draw_normal_ = draw_normal;
	apply_anglecorrection_ = apply_anglecorrection;
	hold_ = hold;
	size_terrain_ = size_terrain;
	sqrt_number_of_patchs_ = sqrt_number_of_patchs;

	VertexCollection vtx_collection_;
	IndexCollection idx_collection_;

	float bigInc = size_terrain_ / sqrt_number_of_patchs_;
	for (unsigned int i = 0; i < sqrt_number_of_patchs_; ++i)
	{
		for (unsigned int j = 0; j < sqrt_number_of_patchs_; ++j)
		{
			//Here we calculate 4 control points
			vtx_collection_.emplace_back(math::float3(bigInc * (i + 0), 0.0f, bigInc * (j + 0)));
			vtx_collection_.emplace_back(math::float3(bigInc * (i + 0), 0.0f, bigInc * (j + 1)));
			vtx_collection_.emplace_back(math::float3(bigInc * (i + 1), 0.0f, bigInc * (j + 1)));
			vtx_collection_.emplace_back(math::float3(bigInc * (i + 1), 0.0f, bigInc * (j + 0)));
		}
	}

	//012321
	idx_collection_.emplace_back(1);
	idx_collection_.emplace_back(2);
	idx_collection_.emplace_back(3);
	idx_collection_.emplace_back(2);
	idx_collection_.emplace_back(1);
	idx_collection_.emplace_back(0);

	directx11_.createTexture(TextureID::WaterBump, "Waterbump.jpg");
	directx11_.createTexture(TextureID::CloudyWave, "cloudyNoon.dds");
	directx11_.createMesh(MeshID::Default, idx_collection_, vtx_collection_, Topology::Patch);
	directx11_.createShader(ShaderID::Default, "Ocean.hlsl");
}

void OceanManager::Renderer()
{
	auto time = directx11_.getShaderVariable<float>(ShaderID::Default, "time");
	auto minDistance = directx11_.getShaderVariable<float>(ShaderID::Default, "minDistance");
	auto maxDistance = directx11_.getShaderVariable<float>(ShaderID::Default, "maxDistance");
	auto minTessExp = directx11_.getShaderVariable<float>(ShaderID::Default, "minTessExp");
	auto maxTessExp = directx11_.getShaderVariable<float>(ShaderID::Default, "maxTessExp");
	auto sizeTerrain = directx11_.getShaderVariable<float>(ShaderID::Default, "sizeTerrain");
	auto applyCorrection = directx11_.getShaderVariable<bool>(ShaderID::Default, "applyCorrection");

	*time = time_;
	*minDistance = min_distance_;
	*maxDistance = max_distance_;
	*minTessExp = min_log2tessfactor_;
	*maxTessExp = max_log2tessfactor_;
	*sizeTerrain = size_terrain_;
	*applyCorrection = apply_anglecorrection_;


	//あとテクスチャーセットするだけ
	directx11_.setShaderResourceFromTexture(0, { TextureID::WaterBump, TextureID::CloudyWave });
	directx11_.setShader(0, ShaderID::Default);
	directx11_.updatePerMeshConstantBuffer();
	directx11_.updateConstantBuffer(ShaderID::Default);
	directx11_.setMesh(MeshID::Default);

	time_ += 0.01f;
}
