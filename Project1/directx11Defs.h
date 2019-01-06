#pragma once

using namespace Seed;

using Device = Microsoft::WRL::ComPtr<ID3D11Device>;
using Context = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;
using SwapChain = Microsoft::WRL::ComPtr<IDXGISwapChain>;

using RenderTargetView = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>;
using ShaderResourceView = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
using DepthStencilView = Microsoft::WRL::ComPtr<ID3D11DepthStencilView>;

using VertexShader = Microsoft::WRL::ComPtr<ID3D11VertexShader>;
using GeometryShader = Microsoft::WRL::ComPtr<ID3D11GeometryShader>;
using HullShader = Microsoft::WRL::ComPtr<ID3D11HullShader>;
using DomainShader = Microsoft::WRL::ComPtr<ID3D11DomainShader>;
using PixelShader = Microsoft::WRL::ComPtr<ID3D11PixelShader>;

using ConstantBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>;
using IndexBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>;
using VertexBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>;
using InputLayout = Microsoft::WRL::ComPtr<ID3D11InputLayout>;

using SamplerState = Microsoft::WRL::ComPtr<ID3D11SamplerState>;
using BlendState = Microsoft::WRL::ComPtr<ID3D11BlendState>;
using RasterizerState = Microsoft::WRL::ComPtr<ID3D11RasterizerState>;

using Vertex = math::float3;
using TextureUV = math::float2;
using Index = unsigned int;
using VertexCollection = std::vector<Vertex>;
struct PolygonTextureUVSet
{
	math::float3 position;
	math::float2 uv;

	PolygonTextureUVSet(math::float3 _pos, math::float2 _uv)
	{
		position = _pos;
		uv = _uv;
	}
};
using VertexCollectionUV = std::vector<PolygonTextureUVSet>;
using IndexCollection = std::vector<Index>;

enum class Topology
{
	PointList,
	LineList,
	LineStrip,
	TriangleList,
	TriangleStrip,
	Patch,
};

enum class Filter
{
	Point,
	Linear,
	Anisotropic
};

enum class AddressMode
{
	Wrap,
	Clamp,
	Mirror,
	MirrorOnce,
	Border
};

enum class BlendType
{
	Zero,
	One,
	SrcColor,
	InvSrcColor,
	SrcAlpha,
	InvSrcAlpha,
	DestAlpha,
	InvDestAlpha,
	DestColor,
	InvDestColor,
	SrcAlphaSat,
	BlendFactor,
	InvBlendFactor,
	Src1Color,
	InvSrc1Color,
	Src1Alpha,
	InvSrc1Alpha
};

enum class BlendOption
{
	Add,
	Subtract,
	RevSubtract,
	Min,
	Max
};

enum class CullMode
{
	None,
	Front,
	Back
};

enum class FillMode
{
	Solid,
	WireFrame
};

struct RenderTarget
{
	RenderTargetView rtv_;
	ShaderResourceView srv_;
};

struct DepthStencil
{
	DepthStencilView dsv_;
};

struct ViewPort
{
	D3D11_VIEWPORT vp_ = {};
};

struct Texture
{
	ShaderResourceView srv_;

	math::float2 size_;
};

struct Shader
{
	VertexShader vs_;
	GeometryShader gs_;
	HullShader hs_;
	DomainShader ds_;
	PixelShader ps_;

	ConstantBuffer cb_;
	InputLayout il_;

	unsigned char * variables_;
	unsigned int variables_size_;
	std::unordered_map<std::string, void*> variables_map_;

	~Shader(void) { if (variables_) delete[] variables_; }
};

struct PerCameraCB
{
	PerCameraCB(void)
		: view_(math::matrix::Identity)
		, projection_(math::matrix::Identity)
		, color_(math::color(1, 1, 1, 1))
		, view_port_(math::float2(0, 0))
		, eye_position_(math::float3(0, 0, 0))
	{}

	math::matrix view_;
	math::matrix projection_;
	math::color color_;
	__declspec(align(16)) math::float2 view_port_;
	__declspec(align(16)) math::float3 eye_position_;
};

struct PerMeshCB
{
	PerMeshCB(void)
		: world_(math::matrix::Identity)
		, diffuse_(math::color(1, 1, 1, 1))
	{}

	math::matrix world_;
	math::color diffuse_;
};

struct Mesh
{
	VertexBuffer vertex_buffer_;
	IndexBuffer index_buffer_;

	unsigned int vertex_cnt_ = 0;
	unsigned int index_cnt_ = 0;

	Topology topology_ = Topology::PointList;
};

struct Sampler
{
	SamplerState sampler_state_;
};

struct Blend
{
	BlendState blend_state_;
};

struct Rasterizer
{
	RasterizerState rasterizer_state_;
};