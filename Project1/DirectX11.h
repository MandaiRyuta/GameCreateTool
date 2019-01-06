#pragma once

#include <windows.h>
#include <unordered_map>
#include <vector>

#include <d3d11.h>
#include <memory>
#include <wrl/client.h>
#include <d3dcompiler.h>

#include "math.h"
#include "resourcePool.h"
#include "directx11Defs.h"
#include "directx11Enums.h"

class DirectX11
{
public:
	DirectX11(void);
	virtual ~DirectX11(void);

public:
	void initialize(void * const handle, const math::float2 & size);

public:
	void * const getHandle(void) const;
	const math::float2 & getSize(void) const;

public:
	void clearRenderTarget(const std::vector<RenderTargetID> & render_target_id_s, const math::color & color);
	void clearDepthStencil(const std::vector<DepthStencilID> & depth_stencil_id_s);
	void setMesh(const MeshID mesh_id, const UINT& InstancingCount = 0);
	void setRenderTargetAndDepthStencil(const std::vector<RenderTargetID> & render_target_id_s, const DepthStencilID & depth_stencil_id);
	void setViewPort(const std::vector<ViewPortID> & view_port_id_s);
	void setShaderResourceFromRenderTarget(const int & start_slot, const std::vector<RenderTargetID> & render_target_id_s);
	void setShaderResourceFromTexture(const int & start_slot, const std::vector<TextureID> & texture_id_s);
	void setShader(const int & shader_slot, const ShaderID & shader_id);
	void setSampler(const int & sampler_slot, const SamplerID & sampler_id);
	void setBlend(const BlendID & blend_id);
	void setDiffuse(const math::color & diffuse);
	void setColor(const math::color & color);
	void setWorld(const math::matrix & world);
	void setView(const math::matrix & view);
	void setProjection(const math::matrix & projection);
	void setRasterizer(const RasterizerID & rasterizer_id);
	void setEyeposition(const math::float3 & eyeposition);
	void updateConstantBuffer(const ShaderID & shader_id);
	void updatePerMeshConstantBuffer(void);
	void updatePerCameraConstantBuffer(void);
	void present(void);
	//void CameraZoom(math::float3 move, float length);
public:
	template<class _Type> _Type * getShaderVariable(const ShaderID & shader_id, const std::string & variable_name)
	{
		return static_cast<_Type*>(this->getShaderVariable(shader_id, variable_name));
	}
private:
	void * getShaderVariable(const ShaderID & shader_id, const std::string & variable_name);
public:
	void createRenderTarget(const RenderTargetID & render_target_id, const DescFormat & format, const math::float2 & size);
	void createDepthStencil(const DepthStencilID & depth_stencil_id, const math::float2 & size);
	void createViewPort(const ViewPortID & view_port_id, const math::float2 & size);
	void createShader(const ShaderID & shader_id, const std::string & file_name);
	void createTexture(const TextureID & texture_id, const std::string & file_name);
	void createSampler(const SamplerID & sampler_id, const Filter & filter, const AddressMode & address_mode);
	void createBlend(const BlendID & blend_id, const BlendOption & blend_option, const BlendType & src, const BlendType & dest, const BlendOption & blend_option_a, const BlendType & src_a, const BlendType & dest_a);
	void createRasterizer(const RasterizerID & rasterizer_id, const CullMode & cull_mode, const FillMode & fill_mode);
	void createMesh(const MeshID & mesh_id, const std::string & file_name);
	void createMesh(const MeshID & mesh_id, const IndexCollection & indices, const VertexCollection & vertices, const Topology & topology = Topology::TriangleList);
	void createTextureMesh(const MeshID & mesh_id, const IndexCollection & indices, const VertexCollectionUV & vertices, const Topology & topology = Topology::TriangleList);
	void releaseRenderTarget(const RenderTargetID & render_target_id);
	void releaseDepthStencil(const DepthStencilID & depth_stencil_id);
	void releaseViewPort(const ViewPortID & view_port_id);
	void releaseShader(const ShaderID & shader_id);
	void releaseTexture(const TextureID & texture_id);
	void releaseSampler(const SamplerID & sampler_id);
	void releaseBlend(const BlendID & blend_id);
	void releaseMesh(const MeshID & mesh_id);
	void InitCamera(const math::float3& eye, const math::float3& at, const math::float3& up);
	void UpdateCamera();
	void CameraChangePitch(float move_amount);
	void CameraChangeYaw(float move_amount);
	void CameraChangeSide(float move_amount);
	void CameraChangeUpDown(float move_amount);
	void IndexedInstancingDraw(const UINT& IdxNumCount, const UINT& InstanceCount);
private:
	Context context_;
	SwapChain swap_chain_;

private:
	HWND handle_;
	math::float2 size_;

private:
	ConstantBuffer per_camera_constant_buffer_;
	ConstantBuffer per_mesh_constant_buffer_;
	PerCameraCB per_camera_cb_;
	PerMeshCB per_mesh_cb_;
	math::float3 DefaultForward;
	math::float3 DefaultRight;
	math::float3 CameraForward;
	math::float3 CameraRight;
	math::matrix CameraRotation;
	math::matrix groundWorld;
	math::float3 Target;
	math::float3 CameraUp;
	math::float3 CameraPosition;
	float moveLeftRight;
	float moveBackForward;

	float CameraYaw;
	float CameraPitch;
private:
	ResourcePool<RenderTarget, RenderTargetID> render_target_db_;
	ResourcePool<DepthStencil, DepthStencilID> depth_stencil_db_;
	ResourcePool<ViewPort, ViewPortID> view_port_db_;
	ResourcePool<Shader, ShaderID> shader_db_;
	ResourcePool<Texture, TextureID> texture_db_;
	ResourcePool<Mesh, MeshID> mesh_db_;
	ResourcePool<Sampler, SamplerID> sampler_db_;
	ResourcePool<Blend, BlendID> blend_db_;
	ResourcePool<Rasterizer, RasterizerID> rasterizer_db_;

	std::unordered_map<std::string, std::unique_ptr<int>> database_;
};