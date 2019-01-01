#include "window.h"

static LRESULT _stdcall WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
	case WM_DESTROY: PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
	}
	return 0;
}

Window::Window()
{

}

Window::~Window()
{
}

const bool Window::Initalize(const std::string& _caption, const unsigned int& _width, const unsigned int& _height)
{
	caption_ = _caption;
	width_ = _width;
	height_ = _height;

	hInstance_ = GetModuleHandleA(nullptr);

	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance_;
	wc.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wc.lpszClassName = caption_.c_str();
	wc.hIconSm = LoadIconA(nullptr, IDI_APPLICATION);
	RegisterClassExA(&wc);

	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = get_width<long>();
	rc.bottom = get_height<long>();
	
	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, true, 0);

	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;

	RECT rc_desk;
	
	GetWindowRect(GetDesktopWindow(), &rc_desk);

	int x = rc_desk.right / 2 - w / 2;
	int y = rc_desk.bottom / 2 - h / 2;

	hWnd_ = CreateWindowExA(0, caption_.c_str(), caption_.c_str(), WS_OVERLAPPEDWINDOW, x, y, w, h, 0, 0, hInstance_, 0);

	ShowWindow(hWnd_, SW_SHOW);

	return true;

}

const bool Window::Run()
{
	MSG msg = {0};
	memset(&msg, 0, sizeof(msg));

	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
		if (msg.message == WM_QUIT)
			return false;
	}
	return true;
}

void Window::Finalize()
{
}

const unsigned int & Window::get_width()
{
	return width_;
}

const unsigned int & Window::get_height()
{
	return height_;
}

void * const Window::get_hwnd()
{
	return hWnd_;
}
