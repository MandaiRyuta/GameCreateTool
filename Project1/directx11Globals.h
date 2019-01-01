#pragma once

#pragma warning (disable: 4100)

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#pragma comment(lib, "dxguid.lib")

#if defined(DEBUG) || defined(_DEBUG)
static constexpr DWORD SHADER_FLAGS = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
#else
static constexpr DWORD SHADER_FLAGS = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

static constexpr const char * k_texture_dir = "data/texture/";
static constexpr const char * k_font_dir = "data/font/";
static constexpr const char * k_shader_dir = "data/shader/";
static constexpr const char * k_mesh_dir = "data/mesh/";

static constexpr const D3D11_PRIMITIVE_TOPOLOGY k_topology_s[] =
{
	D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
	D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
	D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST
};

static constexpr const D3D11_FILTER k_filter_s[] =
{
	D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
	D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
	D3D11_FILTER::D3D11_FILTER_ANISOTROPIC
};

static constexpr const D3D11_TEXTURE_ADDRESS_MODE k_adress_mode_s[] =
{
	D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP,
	D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP,
	D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR,
	D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_MIRROR_ONCE,
	D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER
};

static constexpr const D3D11_BLEND k_blend_type_s[] =
{
	D3D11_BLEND::D3D11_BLEND_ZERO,
	D3D11_BLEND::D3D11_BLEND_ONE,
	D3D11_BLEND::D3D11_BLEND_SRC_COLOR,
	D3D11_BLEND::D3D11_BLEND_INV_SRC_COLOR,
	D3D11_BLEND::D3D11_BLEND_SRC_ALPHA,
	D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA,
	D3D11_BLEND::D3D11_BLEND_DEST_ALPHA,
	D3D11_BLEND::D3D11_BLEND_INV_DEST_ALPHA,
	D3D11_BLEND::D3D11_BLEND_DEST_COLOR,
	D3D11_BLEND::D3D11_BLEND_INV_DEST_COLOR,
	D3D11_BLEND::D3D11_BLEND_SRC_ALPHA_SAT,
	D3D11_BLEND::D3D11_BLEND_BLEND_FACTOR,
	D3D11_BLEND::D3D11_BLEND_INV_BLEND_FACTOR,
	D3D11_BLEND::D3D11_BLEND_SRC1_COLOR,
	D3D11_BLEND::D3D11_BLEND_INV_SRC1_COLOR,
	D3D11_BLEND::D3D11_BLEND_SRC1_ALPHA,
	D3D11_BLEND::D3D11_BLEND_INV_SRC1_ALPHA
};

static constexpr const D3D11_BLEND_OP k_blend_option_s[] =
{
	D3D11_BLEND_OP::D3D11_BLEND_OP_ADD,
	D3D11_BLEND_OP::D3D11_BLEND_OP_SUBTRACT,
	D3D11_BLEND_OP::D3D11_BLEND_OP_REV_SUBTRACT,
	D3D11_BLEND_OP::D3D11_BLEND_OP_MIN,
	D3D11_BLEND_OP::D3D11_BLEND_OP_MAX
};

static constexpr const DXGI_FORMAT k_format_s[] =
{
	DXGI_FORMAT::DXGI_FORMAT_R8_TYPELESS,
	DXGI_FORMAT::DXGI_FORMAT_R8_TYPELESS,
	DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT,
	DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT,
	DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
};

static constexpr const D3D11_CULL_MODE k_cull_mode_s[] =
{
	D3D11_CULL_MODE::D3D11_CULL_NONE,
	D3D11_CULL_MODE::D3D11_CULL_FRONT,
	D3D11_CULL_MODE::D3D11_CULL_BACK
};

static constexpr const D3D11_FILL_MODE k_fill_mode_s[] =
{
	D3D11_FILL_MODE::D3D11_FILL_SOLID,
	D3D11_FILL_MODE::D3D11_FILL_WIREFRAME
};

static DXGI_FORMAT GetDxgiFormat(D3D_REGISTER_COMPONENT_TYPE type, BYTE mask)
{
	if (mask == 0x0F)
	{
		// xyzw
		switch (type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32B32A32_UINT;
		}
	}

	if (mask == 0x07)
	{
		// xyz
		switch (type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32B32_UINT;
		}
	}

	if (mask == 0x3)
	{
		// xy
		switch (type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32_FLOAT;
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32_UINT;
		}
	}

	if (mask == 0x1)
	{
		// x
		switch (type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32_FLOAT;
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32_UINT;
		}
	}

	return DXGI_FORMAT_UNKNOWN;
}

static void CreateConstantBufferFromShader(const Context & device_context, std::unique_ptr<Shader>& shader, ID3DBlob * blob)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	device_context->GetDevice(device.GetAddressOf());

	ID3D11ShaderReflection * reflector = nullptr;
	D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflector);

	D3D11_SHADER_DESC shader_desc;
	reflector->GetDesc(&shader_desc);

	auto cb = reflector->GetConstantBufferByName("unique");

	unsigned int size = 0;
	D3D11_SHADER_BUFFER_DESC desc = {};
	cb->GetDesc(&desc);

	for (unsigned int i = 0; desc.Name != nullptr && i < desc.Variables; ++i)
	{
		auto v = cb->GetVariableByIndex(i);
		D3D11_SHADER_VARIABLE_DESC vdesc;
		v->GetDesc(&vdesc);

		if (vdesc.Size % 16)
			size += vdesc.Size + 16 - (vdesc.Size % 16);
		else
			size += vdesc.Size;
	}

	shader->variables_size_ = size;

	if (size)
		shader->variables_ = new unsigned char[size];

	size = 0;

	for (unsigned int i = 0; desc.Name != nullptr && i < desc.Variables; ++i)
	{
		auto v = cb->GetVariableByIndex(i);
		D3D11_SHADER_VARIABLE_DESC vdesc;
		v->GetDesc(&vdesc);

		shader->variables_map_[vdesc.Name] = shader->variables_ + size;

		if (vdesc.Size % 16)
			size += vdesc.Size + 16 - (vdesc.Size % 16);
		else
			size += vdesc.Size;
	}

	D3D11_BUFFER_DESC bd;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = size;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	bd.Usage = D3D11_USAGE_DEFAULT;

	device->CreateBuffer(&bd, nullptr, shader->cb_.GetAddressOf());
}

static void CreateInputLayoutFromShader(const Context & device_context, std::unique_ptr<Shader>& shader, ID3DBlob * blob)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	device_context->GetDevice(device.GetAddressOf());

	ID3D11ShaderReflection * reflector = nullptr;
	D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflector);

	D3D11_SHADER_DESC shader_desc;
	reflector->GetDesc(&shader_desc);

	std::vector<D3D11_INPUT_ELEMENT_DESC> element;
	for (unsigned int i = 0; i < shader_desc.InputParameters; ++i) {
		D3D11_SIGNATURE_PARAMETER_DESC sigdesc;
		reflector->GetInputParameterDesc(i, &sigdesc);

		auto format = GetDxgiFormat(sigdesc.ComponentType, sigdesc.Mask);

		D3D11_INPUT_ELEMENT_DESC eledesc =
		{
			sigdesc.SemanticName
			, sigdesc.SemanticIndex
			, format
			, 0
			, D3D11_APPEND_ALIGNED_ELEMENT
			, D3D11_INPUT_PER_VERTEX_DATA
			, 0
		};

		element.emplace_back(eledesc);
	}

	if (!element.empty())
		device->CreateInputLayout(&element[0], static_cast<unsigned int>(element.size()),
			blob->GetBufferPointer(), blob->GetBufferSize(), shader->il_.GetAddressOf());
}