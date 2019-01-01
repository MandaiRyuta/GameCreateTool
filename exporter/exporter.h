#pragma once

#include <Windows.h>

extern "C" {
	__declspec(dllexport) void Initialize(HWND hwnd, int size_x, int size_y);
	__declspec(dllexport) void Run(void);
	__declspec(dllexport) void Finalize(void);
	__declspec(dllexport) int add(int a, int b);
	__declspec(dllexport) int* arr_a(int length);
	__declspec(dllexport) void arr_b(int* arr, int length);
}