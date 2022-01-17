/*MIT License

C++ OpenGL 3D Game Tutorial Series (https://github.com/PardCode/OpenGL-3D-Game-Tutorial-Series)

Copyright (c) 2021-2022, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Game/OGame.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <Windows.h>
#include <assert.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		OWindow* window = (OWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return NULL;
}


OWindow::OWindow()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"OGL3DWindow";
	wc.lpfnWndProc = &WndProc;
	wc.style = CS_OWNDC;

	auto classId = RegisterClassEx(&wc);
	assert(classId);

	RECT rc = { 0,0,1024,768 };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	m_handle = CreateWindowEx(NULL, MAKEINTATOM(classId), L"PardCode | OpenGL 3D Game", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);

	assert(m_handle);

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);


	//Creating OpenGL Render Context

	auto hDC = GetDC(HWND(m_handle));

	int pixelFormatAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int pixelFormat = 0;
	UINT numFormats = 0;
	wglChoosePixelFormatARB(hDC, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);
	assert(numFormats);

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);
	SetPixelFormat(hDC, pixelFormat, &pixelFormatDesc);

	int openGLAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	m_context = wglCreateContextAttribsARB(hDC, 0, openGLAttributes);
	assert(m_context);
}

OWindow::~OWindow()
{
	wglDeleteContext(HGLRC(m_context));
	DestroyWindow(HWND(m_handle));
}

void OWindow::makeCurrentContext()
{
	wglMakeCurrent(GetDC(HWND(m_handle)), HGLRC(m_context));
}

void OWindow::present(bool vsync)
{
	wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);
}
