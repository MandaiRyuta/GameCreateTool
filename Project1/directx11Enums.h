#pragma once

enum class ShaderID
{
	Null,
	Default,
};

enum class RenderTargetID
{
	Null,
	Default,
};

enum class DepthStencilID
{
	Null,
	Default,
};

enum class SamplerID
{
	Null,
};

enum class BlendID
{
	Null,
	AlphaADD,
	AlphaINV,
};

enum class RasterizerID
{
	Null,
	CW,
	CCW,
	WF_CW,
	WF_CCW,
	None,
	WF_None
};

enum class ViewPortID
{
	Null,
	Default,
};

enum class MeshID
{
	Null,
	Default,
};

enum class TextureID
{
	Null,
	WaterBump,
	CloudyWave,
	EffectParticle,
};

enum class DescFormat
{
	Null,
	BackBuffer,
	R32F,
	R8G8B8A8UNORM,
	R32G32B32A32F,
};