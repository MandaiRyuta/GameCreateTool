﻿// exporter.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "exporter.h"
#include <iostream>
#include "../Project1/window.h"
#include "../Project1/directx11.h"
#include "../Project1/TerrainManager.h"
#include "../Project1/SkyDomeManager.h"
#include "../Project1/OceanManager.h"

//Window* window;
DirectX11* directx11;
TerrainManager* terrain;
SkyDomeManager* Skydome;
OceanManager* Ocean;

void Initialize(HWND hwnd, int size_x, int size_y)
{
	//window = new Window();
	
	//window->Initalize("hoge", size_x, size_y);

	if (directx11)
		delete directx11;

	if (Skydome)
	{
		delete Skydome;
		Skydome = nullptr;
	}
	if (terrain)
	{
		delete terrain;
		terrain = nullptr;
	}
	if (Ocean)
	{
		delete Ocean;
		Ocean = nullptr;
	}

	directx11 = new DirectX11;

	directx11->initialize(hwnd, math::float2(size_x, size_y));

	directx11->createRenderTarget(RenderTargetID::Default, DescFormat::BackBuffer, directx11->getSize());
	directx11->createDepthStencil(DepthStencilID::Default, directx11->getSize());
	directx11->setRenderTargetAndDepthStencil({ RenderTargetID::Default }, DepthStencilID::Default);
	directx11->InitCamera(math::float3(0.0f,5.0f,-10.0f), math::float3(0.0f,0.0f,0.0f), math::float3(0.0f,1.0f,0.0f));
	directx11->setProjection(math::matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, directx11->getSize().x / directx11->getSize().y, 0.1f, 1000.0f));
	directx11->createRasterizer(RasterizerID::WF_CCW, CullMode::Back, FillMode::Solid);
	directx11->createViewPort(ViewPortID::Default, { directx11->getSize().x ,directx11->getSize().y });
	directx11->setRasterizer(RasterizerID::WF_CCW);
	directx11->setViewPort({ ViewPortID::Default });
	directx11->setEyeposition(math::float3(0.0f, 5.0f, -10.0f));


}

void Reset(HWND hwnd, int size_x, int size_y)
{

	directx11 = new DirectX11;

	directx11->initialize(hwnd, math::float2(size_x, size_y));

	directx11->createRenderTarget(RenderTargetID::Default, DescFormat::BackBuffer, directx11->getSize());
	directx11->createDepthStencil(DepthStencilID::Default, directx11->getSize());
	directx11->setRenderTargetAndDepthStencil({ RenderTargetID::Default }, DepthStencilID::Default);
}

void Run(void)
{
	directx11->clearRenderTarget({ RenderTargetID::Default }, math::color(0.2f, 0.4f, 0.8f, 1.0f));
	directx11->clearDepthStencil({ DepthStencilID::Default });
	directx11->updatePerCameraConstantBuffer();

	if (Skydome != nullptr)
		Skydome->Renderer();
	if (terrain != nullptr)
		terrain->Renderer();
	if (Ocean != nullptr)
		Ocean->Renderer();

	directx11->present();
}

void Finalize(void)
{
}

void CreateTerrain(unsigned int div_x, unsigned int div_y, float frequency, float height, float size_x, float size_y)
{
	if (terrain != nullptr)
	{
		delete terrain;
	}

	terrain = new TerrainManager(*directx11);
	terrain->initialize(div_x, div_y, frequency, height, size_x, size_y);
}

void CreateCube(float size_x, float size_y, float size_z)
{
	if (Skydome != nullptr)
	{
		delete Skydome;
	}

	Skydome = new SkyDomeManager(*directx11);
	Skydome->Cube(math::float3(size_x, size_y, size_z));
}

void CreateSphere(float diameter, unsigned int tessellation)
{
	if (Skydome != nullptr)
	{
		delete Skydome;
	}
	Skydome = new SkyDomeManager(*directx11);
	Skydome->Sphere(diameter, tessellation);
}

void CreateCylinder(float height, float diameter, unsigned int tessellation)
{
	if (Skydome != nullptr)
	{
		delete Skydome;
	}

	Skydome = new SkyDomeManager(*directx11);
	Skydome->Cylinder(height, diameter, tessellation);
}

void CreateOcean(UINT texture_width, UINT texture_height, float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor, bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, unsigned int sqrt_number_of_patchs)
{
	if (Ocean != nullptr)
	{
		delete Ocean;
	}
	Ocean = new OceanManager(*directx11);
	Ocean->Initialize(texture_width, texture_height, time, min_distance, max_distance, min_log2tessfactor, max_log2tessfactor, draw_wires, draw_normal, apply_anglecorrection, hold, size_terrain, sqrt_number_of_patchs);
}

void SetTerrain(unsigned int div_x, unsigned int div_y, float frequency, float height, float size_x, float size_y)
{
	terrain->initialize(div_x, div_y, frequency, height, size_x, size_y);
}

void SetCube(float size_x, float size_y, float size_z)
{
	Skydome->Cube(math::float3(size_x, size_y, size_z));
}

void SetSphere(float diameter, unsigned int tessellation)
{
	Skydome->Sphere(diameter, tessellation);
}

void SetCylinder(float height, float diameter, unsigned int tessellation)
{
	Skydome->Cylinder(height, diameter, tessellation);
}

void SetOcean(UINT texture_width, UINT texture_height, float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor, bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, unsigned int sqrt_number_of_patchs)
{
	Ocean->Initialize(texture_width, texture_height, time, min_distance, max_distance, min_log2tessfactor, max_log2tessfactor, draw_wires, draw_normal, apply_anglecorrection, hold, size_terrain, sqrt_number_of_patchs);
}

void DefaultSetView(float eye_x, float eye_y, float eye_z, float at_x, float at_y, float at_z, float up_x, float up_y, float up_z)
{
	directx11->setView(math::matrix::CreateLookAt({ eye_x, eye_y,eye_z }, { at_x,at_y,at_z }, { up_x,up_y,up_z }));
	directx11->setEyeposition(math::float3(eye_x, eye_y, eye_z));
}

void CameraInit(float eye_x, float eye_y, float eye_z, float at_x, float at_y, float at_z, float up_x, float up_y, float up_z)
{
	directx11->InitCamera({ eye_x, eye_y, eye_z }, { at_x, at_y, at_z }, { up_x, up_y, up_z });
}

void CameraUpdate()
{
	directx11->UpdateCamera();
}

void CameraChangePitch(float move_amount)
{
	directx11->CameraChangePitch(move_amount);
}

void CameraChangeYaw(float move_amount)
{
	directx11->CameraChangeYaw(move_amount);
}

void CameraChangeSide(float move_amount)
{
	directx11->CameraChangeSide(move_amount);
}

void CameraChangeUpDown(float move_amount)
{
	directx11->CameraChangeUpDown(move_amount);
}