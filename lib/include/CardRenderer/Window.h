#pragma once
#include"Includes.h"

class Window
{
public:
	float screen_width = 800, screen_height = 600;
	int* screen_exit;
	int* screen_keys;
	unsigned char* screen_fb;		// frame buffer
	long screen_pitch = 0;

	HWND* screen_handle;

	Window();
	int screen_init(float w, float h, const TCHAR* title);	// 屏幕初始化
	int screen_close(void);								// 关闭屏幕
	void screen_dispatch(void);							// 处理消息
	void screen_update(void);							// 显示 FrameBuffer

	// win32 event handler
	static LRESULT screen_events(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lPar);
};

