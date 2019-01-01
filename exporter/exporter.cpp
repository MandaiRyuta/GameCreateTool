// exporter.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "exporter.h"
#include <iostream>
#include "../Project1/window.h"
#include "../Project1/DirectX11.h"

//Window* window;
DirectX11* directx11;

void Initialize(HWND hwnd, int size_x, int size_y)
{
	//window = new Window();
	
	//window->Initalize("hoge", size_x, size_y);

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
	directx11->present();
}

void Finalize(void)
{
}

int add(int a, int b)
{
	std::cout << "OK!!!!!!" << std::endl;
	return 0;
}

int * arr_a(int length)
{
	return nullptr;
}

void arr_b(int * arr, int length)
{
}
