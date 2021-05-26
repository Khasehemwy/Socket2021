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
	int screen_init(float w, float h, const TCHAR* title);	// ��Ļ��ʼ��
	int screen_close(void);								// �ر���Ļ
	void screen_dispatch(void);							// ������Ϣ
	void screen_update(void);							// ��ʾ FrameBuffer

	// win32 event handler
	static LRESULT screen_events(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lPar);
};

