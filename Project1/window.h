#pragma once

#define WIN32_LEAD_AND_MEAN
#include <Windows.h>

#include <string>

class Window
{
public:
	Window();
	~Window();
public:
	const bool Initalize(const std::string& _caption, const unsigned int& _width, const unsigned int& _height);
	const bool Run();
	void Finalize();
private:
	const unsigned int& get_width();
	const unsigned int& get_height();
	void* const get_hwnd();
public:
	template<class _Type> const _Type get_width() { return static_cast<_Type>(get_width()); }
	template<class _Type> const _Type get_height() { return static_cast<_Type>(get_height()); }
	template<class _Type> const _Type get_hwnd() { return static_cast<_Type>(get_hwnd()); }
private:
	std::string caption_;
	unsigned int width_;
	unsigned int height_;
	HWND hWnd_;
	HINSTANCE hInstance_;
};