#include "GLToolkit.h"

_LGL_BEGIN
GLToolkit::GLToolkit()
{
}

LRESULT GLToolkit::WindowMessageProcesser(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GLToolkit *tk = (GLToolkit *)GetWindowLong(hWnd, GWL_USERDATA);

	switch (uMsg)
	{
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE && tk)
		{
			tk->RemoveGLWindow();
			PostQuitMessage(0);
		}
		break;
	}
	case WM_SIZE:
		tk->ResizeGLWindow({ LOWORD(lParam), HIWORD(lParam) });
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool GLToolkit::CreateGLWindow()
{
	GLuint pixelFormat;
	WNDCLASS windowClass;
	DWORD style, exStyle;
	RECT windowRect = { 0, 0, 1366, 768 };

	hInstance = GetModuleHandle(L"OpenGLiong");
	windowClass.style = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;
	windowClass.lpfnWndProc = (WNDPROC)WindowMessageProcesser;
	windowClass.cbClsExtra = NULL; // No extra
	windowClass.cbWndExtra = sizeof(this); // window data.
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Default icon.
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Default cursor.
	windowClass.hbrBackground = NULL; // No backGround image in need in an opengl application.
	windowClass.lpszMenuName = NULL; // No menu.
	windowClass.lpszClassName = L"LiongStudio_OpenGLiong";

	if (!RegisterClass(&windowClass))
	{
		MessageBox(NULL, L"窗体注册大失败！", L"错误", MB_OK | MB_ICONERROR);
	}

	style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	exStyle = WS_EX_WINDOWEDGE | WS_EX_APPWINDOW;

	AdjustWindowRectEx(&windowRect, style, FALSE, exStyle); // Let: $windowRect = the size of border + area that wa are requiring.

	if (!(hWindow = CreateWindowEx(exStyle, L"LiongStudio_OpenGLiong", L"OpenGLiong", style, 200, 100, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hInstance, NULL)))
	{
		RemoveGLWindow();
		MessageBox(NULL, L"无法创建窗体", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	static PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

	if (!(hDeviceContext = GetDC(hWindow)))
	{
		RemoveGLWindow();
		MessageBox(NULL, L"无法获取设备上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	if (!(pixelFormat = ChoosePixelFormat(hDeviceContext, &pixelFormatDescriptor)))
	{
		RemoveGLWindow();
		MessageBox(NULL, L"无法获取像素格式", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!SetPixelFormat(hDeviceContext, pixelFormat, &pixelFormatDescriptor))
	{
		RemoveGLWindow();
		MessageBox(NULL, L"无法设置像素格式", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!(hRenderingContext = wglCreateContext(hDeviceContext)))
	{
		RemoveGLWindow();
		MessageBox(NULL, L"无法创建渲染上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!wglMakeCurrent(hDeviceContext, hRenderingContext))
	{
		RemoveGLWindow();
		MessageBox(NULL, L"无法绑定渲染上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	SetWindowLong(hWindow, GWLP_USERDATA, (LONG)this);
	ShowWindow(hWindow, SW_SHOW);
	SetForegroundWindow(hWindow);
	SetFocus(hWindow);
	ResizeGLWindow({ 1366, 768 });

	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthFunc(GL_NEVER); // No 3D models will be used.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void GLToolkit::ResizeGLWindow(SIZE size)
{
	GLfloat &&w = (GLfloat)size.cx;
	GLfloat &&h = (GLfloat)size.cy;
	if (h == 0)
		h = 1;
	glViewport(0, 0, size.cx, size.cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = 1.0 * w / h;
	// Set the correct perspective.
	gluPerspective(30, ratio, 0.0f, 100.0f);
	//if (w <= h)
		//glOrtho(0.0f, 0.0f, h / w, h / w, 0.0f, 20.0f);
	//else
		//glOrtho(w / h, w / h, 0, 0, 0.0f, 20.0f);
	//glMatrixMode(GL_MODELVIEW);						// 选择模型观察矩阵
	//glLoadIdentity();
	//       |    摄像机位置   |       中心      |     朝上的点     |
	gluLookAt(0.0f, 0.0f, 33.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void GLToolkit::DrawTestingImage()
{
	glDisable(GL_TEXTURE_2D);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glBegin(GL_QUADS);
	{
		glColor3ub(0, 188, 242);
		
		glVertex2f(-2.6f, 1.6f);
		glVertex2f(-2.6f, -1.6f);
		glVertex2f(2.6f, -2.6f);
		glVertex2f(2.6f, 2.6f);

		glColor3f(0.9f, 0.9f, 0.9f);

		glVertex2f(-0.4f, 2.6f);
		glVertex2f(-0.4f, -2.6f);
		glVertex2f(-0.2f, -2.6f);
		glVertex2f(-0.2f, 2.6f);

		glVertex2f(-2.6f, 0.1f);
		glVertex2f(-2.6f, -0.1f);
		glVertex2f(2.6f, -0.1f);
		glVertex2f(2.6f, 0.1f);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void GLToolkit::SwapGLBuffers()
{
	SwapBuffers(hDeviceContext);
}

void GLToolkit::RemoveGLWindow()
{
	if (hRenderingContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRenderingContext);
		hRenderingContext = NULL;
	}
	if (hDeviceContext && !ReleaseDC(hWindow, hDeviceContext))
		hDeviceContext = NULL;
	if (hWindow && !DestroyWindow(hWindow))
		hWindow = NULL;
	if (!UnregisterClass(L"OpenGLiong", hInstance))
		hInstance = 0;
}

GLToolkit::~GLToolkit()
{
}
_LGL_END