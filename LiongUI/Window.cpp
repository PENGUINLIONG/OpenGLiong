#include "Window.h"

_LUI_BEGIN
Window::Window(SIZE size)
{
	this->size = size;
}

bool Window::Create()
{
	GLuint pixelFormat;
	WNDCLASS windowClass;
	DWORD style, exStyle;
	RECT windowRect = { 0, 0, size.cx, size.cy };

	hInstance = GetModuleHandle(L"OpenGLiong");
	windowClass.style = CS_HREDRAW | CS_OWNDC | CS_VREDRAW;
	windowClass.lpfnWndProc = (WNDPROC)WindowProc;
	windowClass.cbClsExtra = NULL; // No extra
	windowClass.cbWndExtra = sizeof(this); // window data.
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Default icon.
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Default cursor.
	windowClass.hbrBackground = NULL; // No backGround image in need in an opengl application.
	windowClass.lpszMenuName = NULL; // No menu.
	windowClass.lpszClassName = L"OpenGLiong";

	if (!RegisterClass(&windowClass))
	{
		MessageBox(NULL, L"窗体注册大失败！", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	exStyle = WS_EX_WINDOWEDGE | WS_EX_APPWINDOW;

	AdjustWindowRectEx(&windowRect, style, FALSE, exStyle); // Let: $windowRect = the size of border + area that wa are requiring.
	//size_Border = { (windowRect.right - windowRect.left - size.cx) / 2, (windowRect.bottom - windowRect.top - size.cy) / 2 };

	if (!(hWindow = CreateWindowEx(exStyle, L"OpenGLiong", L"OpenGLiong", style, 200, 100, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hInstance, NULL)))
	{
		Remove();
		MessageBox(NULL, L"无法创建窗体", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	static PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

	if (!(hDeviceContext = GetDC(hWindow)))
	{
		Remove();
		MessageBox(NULL, L"无法获取设备上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!(pixelFormat = ChoosePixelFormat(hDeviceContext, &pixelFormatDescriptor)))
	{
		Remove();
		MessageBox(NULL, L"无法获取像素格式", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!SetPixelFormat(hDeviceContext, pixelFormat, &pixelFormatDescriptor))
	{
		Remove();
		MessageBox(NULL, L"无法设置像素格式", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!(hRenderingContext = wglCreateContext(hDeviceContext)))
	{
		Remove();
		MessageBox(NULL, L"无法创建渲染上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}
	if (!wglMakeCurrent(hDeviceContext, hRenderingContext))
	{
		Remove();
		MessageBox(NULL, L"无法绑定渲染上下文", L"错误", MB_OK | MB_ICONERROR);
		return false;
	}

	SetWindowLong(hWindow, GWLP_USERDATA, (LONG)this);
	ShowWindow(hWindow, SW_SHOW);
	SetForegroundWindow(hWindow);
	SetFocus(hWindow);
	Resize(size);

	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthFunc(GL_NEVER); // No 3D models will be used.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Window::Resize(SIZE size)
{
	GLfloat &&w = (GLfloat)size.cx;
	GLfloat &&h = (GLfloat)size.cy;
	if (h == 0)
		h = 1;
	glViewport(0, 0, size.cx , size.cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = 1.0f * w / h;
	// Set the correct perspective.
	gluPerspective(90, ratio, 0.0f, 10.0f);
	if (w <= h)
		glOrtho(0.0f, 0.0f, w / h, w / h, 0.0f, 10.0f);
	else
		glOrtho(h / w, h / w, 0.0f, 0.0f, 0.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);						// 选择模型观察矩阵
	glLoadIdentity();
	//       |    摄像机位置   |       中心      |     朝上的点     |
	gluLookAt(0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	renderer.Resize(size);
	this->size = size;
}

void Window::DrawTestImage()
{
	glDisable(GL_TEXTURE_2D);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glBegin(GL_QUADS);
	{
		glColor3ub(0, 188, 242);

		glVertex2f(-26.0f, 16.0f);
		glVertex2f(-26.0f, -16.0f);
		glVertex2f(26.0f, -26.0f);
		glVertex2f(26.0f, 26.0f);

		glColor3f(0.9f, 0.9f, 0.9f);

		glVertex2f(-4.0f, 26.0f);
		glVertex2f(-4.0f, -26.0f);
		glVertex2f(-2.0f, -26.0f);
		glVertex2f(-2.0f, 26.0f);

		glVertex2f(-26.0f, 1.0f);
		glVertex2f(-26.0f, -1.0f);
		glVertex2f(26.0f, -1.0f);
		glVertex2f(26.0f, 1.0f);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void Window::Remove()
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

void Window::Click(POINT point)
{
	if (entityID == 0)
		return;
	unsigned int i = entityID;
	while (true)
	{
		if (i == 0)
			return;
		i--;
		Entity *&entity = entitys[i];
		if (!entity)
			continue;
		if (entity->GetTag() & EntityType::IClickable)
		{
			IClickable *iClickable = dynamic_cast<IClickable *>(entity);
			if (iClickable && iClickable->CheckClick(size, point))
			{
				iClickable->ClickEventHandler(point);
				return;
			}
		}
	}
}

unsigned int Window::AppendEntity(Entity *Entity)
{
	entitys[entityID] = Entity;
	entityID++;
	return entityID - 1;
}

LRESULT Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window *window = (Window *)GetWindowLong(hWnd, GWL_USERDATA);

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
		case WM_KEYDOWN:
			if (wParam != VK_ESCAPE)
				break;
		case WM_DESTROY:
		case WM_CLOSE:
		{
			if (window)
			{
				window->Remove();
				PostQuitMessage(0);
				return 0;
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			window->Click({ LOWORD(lParam), HIWORD(lParam) });
			return 0;
		}
		case WM_SIZE:
			window->Resize({ LOWORD(lParam), HIWORD(lParam) });
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::~Window()
{
	do
	{
		if (entityID == 0)
			return;
		entityID--;
		Entity *&entity = entitys[entityID];
		if (!entity)
			continue;
		delete entity;
	} while (true);
}
_LUI_END