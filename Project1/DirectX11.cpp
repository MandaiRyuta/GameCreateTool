#include "directx11.h"

#include "DirectXTex\DirectXTex.h"
#include "directx11Globals.h"
#include <iostream>

DirectX11::DirectX11(void)
{
}

DirectX11::~DirectX11(void)
{
}

void DirectX11::initialize(void * const handle, const math::float2 & size)
{
	handle_ = static_cast<HWND>(handle);
	size_ = size;

	Microsoft::WRL::ComPtr<ID3D11Device> device;

	// デバイスとスワップチェーンの作成 
	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = static_cast<unsigned int>(size_.x);
	sd.BufferDesc.Height = static_cast<unsigned int>(size_.y);
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = static_cast<HWND>(handle_);
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	D3D_FEATURE_LEVEL feature_levels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL * feature_level = nullptr;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		0, &feature_levels, 1, D3D11_SDK_VERSION, &sd, swap_chain_.GetAddressOf(), device.GetAddressOf(),
		feature_level, &context_);

	D3D11_BUFFER_DESC bd;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = sizeof(PerCameraCB);
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	bd.Usage = D3D11_USAGE_DEFAULT;

	device->CreateBuffer(&bd, nullptr, per_camera_constant_buffer_.GetAddressOf());

	bd.ByteWidth = sizeof(PerMeshCB);

	device->CreateBuffer(&bd, nullptr, per_mesh_constant_buffer_.GetAddressOf());

	context_->VSSetConstantBuffers(0, 1, per_camera_constant_buffer_.GetAddressOf());
	context_->HSSetConstantBuffers(0, 1, per_camera_constant_buffer_.GetAddressOf());
	context_->DSSetConstantBuffers(0, 1, per_camera_constant_buffer_.GetAddressOf());
	context_->GSSetConstantBuffers(0, 1, per_camera_constant_buffer_.GetAddressOf());
	context_->PSSetConstantBuffers(0, 1, per_camera_constant_buffer_.GetAddressOf());

	context_->VSSetConstantBuffers(1, 1, per_mesh_constant_buffer_.GetAddressOf());
	context_->HSSetConstantBuffers(1, 1, per_mesh_constant_buffer_.GetAddressOf());
	context_->DSSetConstantBuffers(1, 1, per_mesh_constant_buffer_.GetAddressOf());
	context_->GSSetConstantBuffers(1, 1, per_mesh_constant_buffer_.GetAddressOf());
	context_->PSSetConstantBuffers(1, 1, per_mesh_constant_buffer_.GetAddressOf());
}

void * const DirectX11::getHandle(void) const
{
	return handle_;
}

const math::float2 & DirectX11::getSize(void) const
{
	return size_;
}

void DirectX11::clearRenderTarget(const std::vector<RenderTargetID>& render_target_id_s, const math::color & color)
{
	for (auto & id : render_target_id_s)
		context_->ClearRenderTargetView(render_target_db_.Get(id)->rtv_.Get(), color);
}

void DirectX11::clearDepthStencil(const std::vector<DepthStencilID>& depth_stencil_id_s)
{
	for (auto & id : depth_stencil_id_s)
		context_->ClearDepthStencilView(depth_stencil_db_.Get(id)->dsv_.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DirectX11::setMesh(const MeshID mesh_id)
{
	auto& mesh = mesh_db_.Get(mesh_id);
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;
	context_->IASetPrimitiveTopology(k_topology_s[static_cast<unsigned int>(mesh->topology_)]);
	context_->IASetVertexBuffers(0,1,mesh->vertex_buffer_.GetAddressOf(), &stride, &offset);
	context_->IASetIndexBuffer(mesh->index_buffer_.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	context_->DrawIndexed(mesh->index_cnt_, 0, 0);
}

void DirectX11::setRenderTargetAndDepthStencil(const std::vector<RenderTargetID>& render_target_id_s, const DepthStencilID & depth_stencil_id)
{
	std::vector<ID3D11RenderTargetView*> rtvs_;

	for (auto & id : render_target_id_s)
		rtvs_.emplace_back(render_target_db_.Get(id)->rtv_.Get());

	ID3D11DepthStencilView * dsv = nullptr;

	if (depth_stencil_id != DepthStencilID::Null)
		dsv = depth_stencil_db_.Get(depth_stencil_id)->dsv_.Get();

	context_->OMSetRenderTargets(static_cast<unsigned int>(rtvs_.size()), rtvs_.data(), dsv);
}

void DirectX11::setViewPort(const std::vector<ViewPortID>& view_port_id_s)
{
	std::vector<D3D11_VIEWPORT> view_ports;

	for (auto & id : view_port_id_s)
		view_ports.emplace_back(view_port_db_.Get(id)->vp_);

	context_->RSSetViewports(static_cast<unsigned int>(view_ports.size()), view_ports.data());
}

void DirectX11::setShaderResourceFromRenderTarget(const int & start_slot, const std::vector<RenderTargetID> & render_target_id_s)
{
	std::vector<ID3D11ShaderResourceView*> srvs_;

	for (auto & id : render_target_id_s)
		srvs_.emplace_back(render_target_db_.Get(id)->srv_.Get());

	context_->PSSetShaderResources(start_slot, static_cast<int>(render_target_id_s.size()), srvs_.data());
}

void DirectX11::setShaderResourceFromTexture(const int & start_slot, const std::vector<TextureID> & texture_id_s)
{
	std::vector<ID3D11ShaderResourceView*> srvs_;

	for (auto & id : texture_id_s)
		srvs_.emplace_back(texture_db_.Get(id)->srv_.Get());

	context_->PSSetShaderResources(start_slot, static_cast<int>(texture_id_s.size()), srvs_.data());
}

void DirectX11::setShader(const int & shader_slot, const ShaderID & shader_id)
{
	auto & shader = shader_db_.Get(shader_id);

	context_->IASetInputLayout(shader->il_.Get());

	context_->VSSetShader(shader->vs_.Get(), nullptr, 0);
	context_->GSSetShader(shader->gs_.Get(), nullptr, 0);
	context_->HSSetShader(shader->hs_.Get(), nullptr, 0);
	context_->DSSetShader(shader->ds_.Get(), nullptr, 0);
	context_->PSSetShader(shader->ps_.Get(), nullptr, 0);

	context_->VSSetConstantBuffers(2, 1, shader->cb_.GetAddressOf());
	context_->GSSetConstantBuffers(2, 1, shader->cb_.GetAddressOf());
	context_->HSSetConstantBuffers(2, 1, shader->cb_.GetAddressOf());
	context_->DSSetConstantBuffers(2, 1, shader->cb_.GetAddressOf());
	context_->PSSetConstantBuffers(2, 1, shader->cb_.GetAddressOf());
}

void DirectX11::setSampler(const int & sampler_slot, const SamplerID & sampler_id)
{
	auto & sampler = sampler_db_.Get(sampler_id);
	context_->PSSetSamplers(sampler_slot, 1, sampler->sampler_state_.GetAddressOf());
}

void DirectX11::setBlend(const BlendID & blend_id)
{
	auto & blend = blend_db_.Get(blend_id);
	context_->OMSetBlendState(blend->blend_state_.Get(), nullptr, 0xffffffff);
}

void DirectX11::setDiffuse(const math::color & diffuse)
{
	per_mesh_cb_.diffuse_ = diffuse;
}

void DirectX11::setColor(const math::color & color)
{
	per_camera_cb_.color_ = color;
}

void DirectX11::setWorld(const math::matrix & world)
{
	per_mesh_cb_.world_ = world;
}

void DirectX11::setView(const math::matrix & view)
{
	per_camera_cb_.view_ = view;
}

void DirectX11::setProjection(const math::matrix & projection)
{
	per_camera_cb_.projection_ = projection;
}

void DirectX11::setRasterizer(const RasterizerID & rasterizer_id)
{
	context_->RSSetState(rasterizer_db_.Get(rasterizer_id)->rasterizer_state_.Get());
}

void DirectX11::setEyeposition(const math::float3 & eyeposition)
{
	per_camera_cb_.eye_position_ = eyeposition;
}

void DirectX11::updateConstantBuffer(const ShaderID & shader_id)
{
	auto & shader = shader_db_.Get(shader_id);

	context_->UpdateSubresource(shader->cb_.Get(), 0, nullptr, shader->variables_, 0, 0);
}

void DirectX11::updatePerMeshConstantBuffer(void)
{
	context_->UpdateSubresource(per_mesh_constant_buffer_.Get(), 0, nullptr, &per_mesh_cb_, 0, 0);
}

void DirectX11::updatePerCameraConstantBuffer(void)
{
	context_->UpdateSubresource(per_camera_constant_buffer_.Get(), 0, nullptr, &per_camera_cb_, 0, 0);
}

void DirectX11::createRenderTarget(const RenderTargetID & render_target_id, const DescFormat & format, const math::float2 & size)
{
	auto render_target = std::make_unique<RenderTarget>();

	Microsoft::WRL::ComPtr<ID3D11Device> device;

	context_->GetDevice(device.GetAddressOf());

	if (format == DescFormat::BackBuffer)
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;

		swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&tex_2d);

		device->CreateRenderTargetView(tex_2d.Get(), nullptr, render_target->rtv_.GetAddressOf());
	}
	else
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;

		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
		D3D11_RENDER_TARGET_VIEW_DESC RTVDesc = {};
		D3D11_TEXTURE2D_DESC desc = {};

		desc.Width = static_cast<unsigned int>(size.x);
		desc.Height = static_cast<unsigned int>(size.y);
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R32_FLOAT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		device->CreateTexture2D(&desc, nullptr, tex_2d.GetAddressOf());

		RTVDesc.Format = desc.Format;
		RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		RTVDesc.Texture2D.MipSlice = 0;
		device->CreateRenderTargetView(tex_2d.Get(), &RTVDesc, render_target->rtv_.GetAddressOf());

		SRVDesc.Format = desc.Format;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = 1;
		device->CreateShaderResourceView(tex_2d.Get(), &SRVDesc, render_target->srv_.GetAddressOf());
	}

	render_target_db_.Load(render_target_id, render_target);
}

void DirectX11::createDepthStencil(const DepthStencilID & depth_stencil_id, const math::float2 & size)
{
	auto depth_stencil = std::make_unique<DepthStencil>();

	Microsoft::WRL::ComPtr<ID3D11Device> device;

	context_->GetDevice(device.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;

	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = static_cast<unsigned int>(size.x);
	tex_desc.Height = static_cast<unsigned int>(size.y);
	tex_desc.MipLevels = 1;
	tex_desc.ArraySize = 1;
	tex_desc.Format = DXGI_FORMAT_D32_FLOAT;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.CPUAccessFlags = 0;
	tex_desc.MiscFlags = 0;

	device->CreateTexture2D(&tex_desc, nullptr, tex_2d.GetAddressOf());
	device->CreateDepthStencilView(tex_2d.Get(), nullptr, depth_stencil->dsv_.GetAddressOf());

	depth_stencil_db_.Load(depth_stencil_id, depth_stencil);
}

void DirectX11::createViewPort(const ViewPortID & view_port_id, const math::float2 & size)
{
	auto view_port = std::make_unique<ViewPort>();

	view_port->vp_.Width = static_cast<float>(size.x);
	view_port->vp_.Height = static_cast<float>(size.y);
	view_port->vp_.MaxDepth = 1.f;
	view_port->vp_.MinDepth = 0.f;
	view_port->vp_.TopLeftX = 0;
	view_port->vp_.TopLeftY = 0;

	return view_port_db_.Load(view_port_id, view_port);
}

void DirectX11::createShader(const ShaderID & shader_id, const std::string & file_name)
{
	auto file_path = k_shader_dir + file_name;

	auto shader = std::make_unique<Shader>();

	Microsoft::WRL::ComPtr<ID3D11Device> device;

	context_->GetDevice(device.GetAddressOf());

	ID3DBlob * blob = nullptr;
	ID3DBlob * error = nullptr;

	if (FAILED(D3DCompileFromFile(std::wstring(file_path.begin(), file_path.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		if (error)
		{
			char * err = (char*)error->GetBufferPointer();
			if (error != nullptr)
				MessageBoxA(nullptr, (LPCSTR)err, nullptr, MB_OK);
		}
	}
	else
	{
		device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader->vs_.GetAddressOf());
		CreateInputLayoutFromShader(context_, shader, blob);
		CreateConstantBufferFromShader(context_, shader, blob);
	}

	if (SUCCEEDED(D3DCompileFromFile(std::wstring(file_path.begin(), file_path.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS", "gs_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader->gs_.GetAddressOf());
		if (shader->cb_ == nullptr)
			CreateConstantBufferFromShader(context_, shader, blob);
	}

	if (SUCCEEDED(D3DCompileFromFile(std::wstring(file_path.begin(), file_path.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "HS", "hs_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		device->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader->hs_.GetAddressOf());
		if (shader->cb_ == nullptr)
			CreateConstantBufferFromShader(context_, shader, blob);
	}

	if (SUCCEEDED(D3DCompileFromFile(std::wstring(file_path.begin(), file_path.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "DS", "ds_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		device->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader->ds_.GetAddressOf());
		if (shader->cb_ == nullptr)
			CreateConstantBufferFromShader(context_, shader, blob);
	}

	if (SUCCEEDED(D3DCompileFromFile(std::wstring(file_path.begin(), file_path.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader->ps_.GetAddressOf());
		if (shader->cb_ == nullptr)
			CreateConstantBufferFromShader(context_, shader, blob);
	}

	std::cout << "xxxx" << std::endl;

	if (!shader->vs_)
	{
		MessageBoxA(nullptr, "dssfdasf", nullptr, MB_OK);
	}

	shader_db_.Load(shader_id, shader);
}

void DirectX11::createTexture(const TextureID & texture_id, const std::string & file_name)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	context_->GetDevice(device.GetAddressOf());

	auto file_path = k_texture_dir + file_name;

	auto texture = std::make_unique<Texture>();

	DirectX::ScratchImage ximage;

	DirectX::LoadFromWICFile(std::wstring(file_path.begin(), file_path.end()).c_str(), DirectX::WIC_FLAGS_NONE, nullptr, ximage);

	auto image = std::make_unique<DirectX::ScratchImage>();
	DirectX::GenerateMipMaps(ximage.GetImages(), ximage.GetImageCount(), ximage.GetMetadata(), DirectX::TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT, 0, *image);

	texture->size_.x = static_cast<float>(image->GetMetadata().width);
	texture->size_.y = static_cast<float>(image->GetMetadata().height);

	DirectX::CreateShaderResourceView(device.Get(), image->GetImages(), image->GetImageCount(), image->GetMetadata(), texture->srv_.GetAddressOf());

	texture_db_.Load(texture_id, texture);
}

void DirectX11::createSampler(const SamplerID & sampler_id, const Filter & filter, const AddressMode & address_mode)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	context_->GetDevice(device.GetAddressOf());

	auto sampler = std::make_unique<Sampler>();

	D3D11_SAMPLER_DESC desc = {};

	desc.Filter = k_filter_s[static_cast<unsigned int>(filter)];

	desc.AddressU = k_adress_mode_s[static_cast<unsigned int>(address_mode)];
	desc.AddressV = k_adress_mode_s[static_cast<unsigned int>(address_mode)];
	desc.AddressW = k_adress_mode_s[static_cast<unsigned int>(address_mode)];

	desc.MaxAnisotropy = (device->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? D3D11_MAX_MAXANISOTROPY : 2;

	desc.MaxLOD = FLT_MAX;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	device->CreateSamplerState(&desc, sampler->sampler_state_.GetAddressOf());

	sampler_db_.Load(sampler_id, sampler);
}

void DirectX11::createBlend(const BlendID & blend_id, const BlendOption & blend_option, const BlendType & src, const BlendType & dest, const BlendOption & blend_option_a, const BlendType & src_a, const BlendType & dest_a)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	context_->GetDevice(device.GetAddressOf());

	auto blend = std::make_unique<Blend>();

	D3D11_BLEND_DESC desc = {};

	desc.AlphaToCoverageEnable = false;

	desc.IndependentBlendEnable = false;

	desc.RenderTarget[0].BlendEnable = true;

	desc.RenderTarget[0].SrcBlend = k_blend_type_s[static_cast<unsigned int>(src)];
	desc.RenderTarget[0].DestBlend = k_blend_type_s[static_cast<unsigned int>(dest)];
	desc.RenderTarget[0].BlendOp = k_blend_option_s[static_cast<unsigned int>(blend_option)];

	desc.RenderTarget[0].SrcBlendAlpha = k_blend_type_s[static_cast<unsigned int>(src_a)];
	desc.RenderTarget[0].DestBlendAlpha = k_blend_type_s[static_cast<unsigned int>(dest_a)];
	desc.RenderTarget[0].BlendOpAlpha = k_blend_option_s[static_cast<unsigned int>(blend_option_a)];

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	device->CreateBlendState(&desc, blend->blend_state_.GetAddressOf());

	blend_db_.Load(blend_id, blend);
}

void DirectX11::createRasterizer(const RasterizerID & rasterizer_id, const CullMode & cull_mode, const FillMode & fill_mode)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	context_->GetDevice(device.GetAddressOf());

	auto rasterizer = std::make_unique<Rasterizer>();

	D3D11_RASTERIZER_DESC desc = {};

	desc.CullMode = k_cull_mode_s[static_cast<unsigned int>(cull_mode)];
	desc.FillMode = k_fill_mode_s[static_cast<unsigned int>(fill_mode)];

	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;

	device->CreateRasterizerState(&desc, rasterizer->rasterizer_state_.GetAddressOf());

	rasterizer_db_.Load(rasterizer_id, rasterizer);
}

void DirectX11::createMesh(const MeshID & mesh_id, const std::string & file_name)
{
	auto file_path = k_mesh_dir + file_name;

	auto mesh = std::make_unique<Mesh>();

	return mesh_db_.Load(mesh_id, mesh);
}

void DirectX11::createMesh(const MeshID & mesh_id, const IndexCollection & indices, const VertexCollection & vertices, const Topology & topology)
{

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	context_->GetDevice(device.GetAddressOf());

	auto mesh = std::make_unique<Mesh>();

	{
		mesh->vertex_cnt_ = vertices.size();
		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = mesh->vertex_cnt_ * sizeof(Vertex);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();

		device->CreateBuffer(&bd, &sd, mesh->vertex_buffer_.GetAddressOf());
	}

	{
		mesh->index_cnt_ = indices.size();
		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = mesh->index_cnt_ * sizeof(Index);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = indices.data();

		device->CreateBuffer(&bd, &sd, mesh->index_buffer_.GetAddressOf());
	}

	mesh->topology_ = topology;

	return mesh_db_.Load(mesh_id, mesh);
}

void DirectX11::releaseRenderTarget(const RenderTargetID & render_target_id)
{
	render_target_db_.Unload(render_target_id);
}

void DirectX11::releaseDepthStencil(const DepthStencilID & depth_stencil_id)
{
	depth_stencil_db_.Unload(depth_stencil_id);
}

void DirectX11::releaseViewPort(const ViewPortID & view_port_id)
{
	view_port_db_.Unload(view_port_id);
}

void DirectX11::releaseShader(const ShaderID & shader_id)
{
	shader_db_.Unload(shader_id);
}

void DirectX11::releaseTexture(const TextureID & texture_id)
{
	texture_db_.Unload(texture_id);
}

void DirectX11::releaseSampler(const SamplerID & sampler_id)
{
	sampler_db_.Unload(sampler_id);
}

void DirectX11::releaseBlend(const BlendID & blend_id)
{
	blend_db_.Unload(blend_id);
}

void DirectX11::releaseMesh(const MeshID & mesh_id)
{
	mesh_db_.Unload(mesh_id);
}

void DirectX11::present(void)
{
	swap_chain_->Present(0, 0);
}

void * DirectX11::getShaderVariable(const ShaderID & shader_id, const std::string & variable_name)
{
	return shader_db_.Get(shader_id)->variables_map_[variable_name];
}
