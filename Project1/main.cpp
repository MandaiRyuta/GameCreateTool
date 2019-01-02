//#include "window.h"
//#include <crtdbg.h>
//#include "DirectX11.h"
//#include "TerrainManager.h"
//#include "SkyDomeManager.h"
//#include "SeaManager.h"
//#include "OceanManager.h"
//int _stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
//{
//#ifdef _DEBUG
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
//	Window window;
//	DirectX11 renderer;
//	//ToolObjectManager te(renderer);
//	//SkyDomeManager te2(renderer);
//	//SeaManager te3(renderer);
//	OceanManager te4(renderer);
//
//	window.Initalize("Test", 1280U, 720U);
//	renderer.initialize(window.get_hwnd<HWND>(), { window.get_width<float>(), window.get_height<float>() });
//	renderer.createRenderTarget(RenderTargetID::Default, DescFormat::BackBuffer,renderer.getSize());
//	renderer.createDepthStencil(DepthStencilID::Default, renderer.getSize());
//	renderer.setRenderTargetAndDepthStencil({ RenderTargetID::Default }, DepthStencilID::Default);
//	renderer.setView(math::matrix::CreateLookAt({ 0.0f,15.0f,-10.0f }, { 2000.0f/2.0f,0.0f,2000.0f/2.0f }, { 0.0f,1.0f,0.0f }));
//	renderer.setProjection(math::matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, renderer.getSize().x / renderer.getSize().y, 0.1f, 1000.0f));
//	renderer.createRasterizer(RasterizerID::WF_CCW, CullMode::Back, FillMode::Solid);
//	renderer.createViewPort(ViewPortID::Default, { renderer.getSize().x ,renderer.getSize().y });
//	renderer.setRasterizer(RasterizerID::WF_CCW);
//	renderer.setViewPort({ ViewPortID::Default });
//	renderer.setEyeposition(math::float3(0.0f,15.0f,-10.0f));
//	//te.initialize(100, 100, 100.0f, 100.0f);
//	//te2.initialize();
//	//te3.initialize(100,100,100.0f,100.0f);
//	te4.Initialize(1024, 1024, 0.0f, -100.0f, 100.0f, 1.0f, 5.0f, false, false, false, false, 2000.0f, 8);
//	while (window.Run())
//	{
//		renderer.clearRenderTarget({ RenderTargetID::Default }, math::color(0.2f, 0.4f, 0.8f, 1.0f));
//		renderer.clearDepthStencil({ DepthStencilID::Default });
//		renderer.updatePerCameraConstantBuffer();
//
//		//te.Renderer();
//		//te2.Renderer();
//		//te3.Renderer();
//		te4.Renderer();
//		renderer.present();
//	}
//
//	window.Finalize();
//
//	return 0;
//}