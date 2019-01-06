#pragma once

#include <Windows.h>

extern "C" {
	__declspec(dllexport) void Initialize(HWND hwnd, int size_x, int size_y);
	__declspec(dllexport) void Reset(HWND hwnd, int size_x, int size_y);
	__declspec(dllexport) void Run(void);
	__declspec(dllexport) void Finalize(void);

	__declspec(dllexport) void DefaultSetView(float eye_x, float eye_y, float eye_z, float at_x, float at_y, float at_z, float up_x, float up_y, float up_z);
	__declspec(dllexport) void CameraUpdate();
	__declspec(dllexport) void CameraInit(float eye_x, float eye_y, float eye_z, float at_x, float at_y, float at_z, float up_x, float up_y, float up_z);
	__declspec(dllexport) void CameraChangePitch(float move_amount);
	__declspec(dllexport) void CameraChangeYaw(float move_amount);
	__declspec(dllexport) void CameraChangeSide(float move_amount);
	__declspec(dllexport) void CameraChangeUpDown(float move_amount);

	/*Create*/
	__declspec(dllexport) void CreateTerrain(unsigned int div_x, unsigned int div_y, float frequency, float height, float size_x, float size_y);
	__declspec(dllexport) void CreateCube(float size_x, float size_y, float size_z);
	__declspec(dllexport) void CreateSphere(float diameter, unsigned int tessellation);
	__declspec(dllexport) void CreateCylinder(float height, float diameter, unsigned int tessellation);
	__declspec(dllexport) void CreateOcean(UINT texture_width, UINT texture_height, float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor,
		bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, unsigned int sqrt_number_of_patchs);

	/*Set*/
	__declspec(dllexport) void SetTerrain(unsigned int div_x, unsigned int div_y, float frequency, float height, float size_x, float size_y);
	__declspec(dllexport) void SetCube(float size_x, float size_y, float size_z);
	__declspec(dllexport) void SetSphere(float diameter, unsigned int tessellation);
	__declspec(dllexport) void SetCylinder(float height, float diameter, unsigned int tessellation);
	__declspec(dllexport) void SetOcean(UINT texture_width, UINT texture_height, float time, float min_distance, float max_distance, float min_log2tessfactor, float max_log2tessfactor,
		bool draw_wires, bool draw_normal, bool apply_anglecorrection, bool hold, float size_terrain, unsigned int sqrt_number_of_patchs);
}