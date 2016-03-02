#include "OGLWindow.h"
#include "OGLWindowMaker.h"
#include "Resource.h"
#include <gl/GL.h>
#include "freeglut.h"

RECT windowSize;

OGLWindow::OGLWindow()
{

}

OGLWindow::~OGLWindow()
{
	//DestroyOGLContext();
	
	//Clean up the renderable
	delete photoViewer;
	delete m_startbar; 
	delete colourSelector; 
}

OGLWindow::OGLWindow(HINSTANCE hInstance, int width, int height)
{
	InitWindow(hInstance, width, height);
}

HGLRC OGLWindow::CreateOGLContext(HDC hdc)
{
	unsigned int pixelformat;
	HGLRC hglrc;

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support Window
		PFD_SUPPORT_OPENGL |						// Format Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request RGBA Format
		32,											// Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits mask
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// Z-Buffer depth
		0,											// Stencil Buffer
		0,											// Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(pixelformat=ChoosePixelFormat(hdc,&pfd)))
	{
		return 0;
	}

	if(!SetPixelFormat(hdc,pixelformat,&pfd))
	{
		return 0;
	}

	if (!(hglrc=wglCreateContext(hdc)))
	{
		return 0;
	}

	if(!wglMakeCurrent(hdc,hglrc))
	{
		return 0;
	}

	return hglrc;
}

void OGLWindow::DestroyOGLWindow()
{
	DestroyOGLContext();

	DestroyWindow( m_hwnd );

	m_hwnd = NULL;
	m_hdc = NULL;
}


BOOL OGLWindow::DestroyOGLContext()
{
	if ( m_hglrc )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( m_hglrc );
		m_hglrc = NULL;
	}
	
	if ( !ReleaseDC ( m_hwnd, m_hdc ) )
		return FALSE;

	return TRUE;
}

BOOL OGLWindow::InitWindow(HINSTANCE hInstance, int width, int height)
{
	InitOGLState();

	m_hwnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		L"OGLWindow", L"OpenGL 95", WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
		0, 0, width, height, NULL, NULL, hInstance, NULL);

	if ( ! m_hwnd )
		return FALSE;

	m_hdc = GetDC( m_hwnd );

	if ( !(m_hglrc = CreateOGLContext( m_hdc )) )
		return FALSE;
	
	m_width = width;
	m_height = height;

	WindowSize(&windowRect);
	WindowSize2(&windowRect);

	GetClientRect(m_hwnd, &windowRect);

	glClearColor((77 / 255.0f), (153 / 255.0f), (153 / 255.0f), 0.0f);

	//Instantiate a Renderable
	photoViewer = new OGLWindowMaker("Photo Viewer", 0, 200, OGLWindowMaker::PhotoViewer);
	colourSelector = new OGLWindowMaker("Colour Select", -50, 250, OGLWindowMaker::ColourSelect);
	colourSelectorIcon = new DesktopIcon( ((windowRect.left - windowRect.right) * 0.5) + 10.0f, ((windowRect.bottom - windowRect.top) * 0.5) - 10.0f , DesktopIcon::ColourSelector);
	photoViewerIcon = new DesktopIcon(((windowRect.left - windowRect.right) * 0.5) + 10.0f, ((windowRect.bottom - windowRect.top) * 0.5) - 100.0f, DesktopIcon::PhotoViewer);

	m_startbar = new OGLStartBar();

	render[0] = photoViewer;
	render[1] = colourSelector;
	photoViewer->SetTopBarFocused(true);

	renderWindow = static_cast<Renderable*>(render[0]);
	renderWindow2 = static_cast<Renderable*>(render[1]);

	renderStartbar = static_cast<Renderable*>(m_startbar);
	return TRUE;
}

void OGLWindow::SetVisible ( BOOL visible )
{
	ShowWindow ( m_hwnd, visible? SW_SHOW : SW_HIDE );
}

void OGLWindow::SetDesktopColour(float red, float green, float blue)
{
	desktopRed = red; 
	desktopGreen = green; 
	desktopBlue = blue; 
}

void OGLWindow::Render()
{
	glClearColor((desktopRed / 255.0f), (desktopGreen / 255.0f), (desktopBlue / 255.0f), 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();

	colourSelectorIcon->Render();
	colourSelectorIcon->setXY(((windowRect.left - windowRect.right) * 0.5) + 30.0f, ((windowRect.bottom - windowRect.top) * 0.5) - 10.0f);
	photoViewerIcon->Render();
	photoViewerIcon->setXY(((windowRect.left - windowRect.right) * 0.5) + 30.0f, ((windowRect.bottom - windowRect.top) * 0.5) - 100.0f);

		if (render[1] == colourSelector)
		{
			if (!colourSelector->closeWindow())
			{
				renderWindow2->Render();
			}
		}

		glEnable(GL_BLEND);
		if  (render[1] == photoViewer)
		{
			if (!photoViewer->closeWindow())
			{
				renderWindow->Render();
			}
		}

		glEnable(GL_BLEND);
		if (render[0] == colourSelector)
		{
			if (!colourSelector->closeWindow())
			{
				renderWindow2->Render();
			}
		}	

		glEnable(GL_BLEND);
		if (render[0] == photoViewer)
		{
			if (!photoViewer->closeWindow())
			{
				renderWindow->Render();
			}
		}

	photoViewer->SetTopBarColour(colourSelector->topBarRed, colourSelector->topBarGreen, colourSelector->topBarBlue);
	colourSelector->SetTopBarColour(colourSelector->topBarRed, colourSelector->topBarGreen, colourSelector->topBarBlue);

	//Always renders the startbar last because it should always be on top 
	m_startbar->SetBarColour(colourSelector->startbarRed, colourSelector->startbarGreen, colourSelector->startbarBlue);
	renderStartbar->Render();

	SetDesktopColour(colourSelector->desktopRed, colourSelector->desktopGreen, colourSelector->desktopBlue);
	glFlush();
	SwapBuffers(m_hdc);
	return;
}

void OGLWindow::Resize( int width, int height )
{
	glViewport( 0, 0, width, height );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -0.5*width , 0.5*width , -0.5*height , 0.5*height , -1.0 , 1.0);

	GetClientRect(m_hwnd, &windowRect);			//Gets the new client size after resizing
	WindowSize(&windowRect);					//Returns the new client size in the form of a RECT
	WindowSize2(&windowRect);

	//Deletes the old start bar on resize
	delete m_startbar;

	//Makes a new one with the new resized dimension
	m_startbar = new OGLStartBar();
	Renderable* renderStartbar = static_cast<Renderable*>(m_startbar);
		renderStartbar->Render();
	glFlush();

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	return;
}

void OGLWindow::InitOGLState()
{
	glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

RECT WindowSize(RECT *windowSize)
{
	return *windowSize;
}

RECT WindowSize2(RECT *windowSize)
{
	return *windowSize;
}

BOOL OGLWindow::MouseLBDown(int x, int y)
{
	Listener *LBDWindow = static_cast<Listener*>(photoViewer);
	Listener *LBDWindow2 = static_cast<Listener*>(colourSelector);
	Listener *LBDStartBarListener = static_cast<Listener*>(m_startbar);

	LBDWindow->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));
	LBDWindow2->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));

	if (!colourSelector->closeWindow())
	{
		if (colourSelector->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)) == true && photoViewer->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)) == false)
		{
			render[0] = colourSelector;
			colourSelector->SetTopBarFocused(true);
			render[1] = photoViewer;
			photoViewer->SetTopBarFocused(false);
		}
	}
	if (!photoViewer->closeWindow())
	{
		if (photoViewer->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)) == true && colourSelector->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)) == false)
		{
			render[0] = photoViewer;
			photoViewer->SetTopBarFocused(true);
			render[1] = colourSelector;
			colourSelector->SetTopBarFocused(false);
		}
	}
	if (photoViewer->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)) == true && colourSelector->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)) == true)
	{
		render[0]->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));
	}

	if (photoViewer->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)) == false && colourSelector->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)) == false)
	{
		photoViewer->SetTopBarFocused(false);
		colourSelector->SetTopBarFocused(false);
	}

	LBDStartBarListener->MouseLBDown(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));
	
	return TRUE;
}

BOOL OGLWindow::MouseLBUp ( int x, int y )
{
	Listener *LBUWindow = static_cast<Listener*>(photoViewer);
	Listener *LBUWindow2 = static_cast<Listener*>(colourSelector);
	Listener *LBUStartbar = static_cast<Listener*>(m_startbar);
	Listener *LBUColourSelectIcon = static_cast<Listener*>(colourSelectorIcon);
	Listener *LBUPhotoViewer = static_cast<Listener*>(photoViewerIcon);

	if (!photoViewer->closeWindow())
	{
		LBUWindow->MouseLBUp(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));
	}

	if (!colourSelector->closeWindow())
	{
		LBUWindow2->MouseLBUp(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));
	}
	
	if (LBUColourSelectIcon->MouseLBUp(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)))
	{
		colourSelector->openWindow(false);
		if (render[0] != colourSelector)
		{
			render[1] = render[0];
			render[0] = colourSelector;
			render[0]->SetTopBarFocused(true);
			render[1]->SetTopBarFocused(false);
		}
		
	}

	if (LBUPhotoViewer->MouseLBUp(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5)))
	{
		photoViewer->openWindow(false);
		if (render[0] != photoViewer)
		{
			render[1] = render[0];
			render[0] = photoViewer;
			if (render[1] != photoViewer)
			{
				render[0]->SetTopBarFocused(true);
				render[1]->SetTopBarFocused(false);
			}
			else
			{
				render[0]->SetTopBarFocused(true);
			}
		}
	}

	LBUStartbar->MouseLBUp(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));

	return TRUE;
}

BOOL OGLWindow::MouseMove ( int x, int y )
{
	Listener *windowListener = static_cast<Listener*>(photoViewer);
	Listener *windowListener2 = static_cast<Listener*>(colourSelector);	
	Listener *StartBarListener = static_cast<Listener*>(m_startbar);

	if (!render[0]->closeWindow())
	{
		render[0]->MouseMove(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));
	}


	StartBarListener->MouseMove(x - (windowRect.right * 0.5), -y + (windowRect.bottom * 0.5));

	return TRUE;
}

BOOL OGLWindow::MouseRBDown(int x, int y)
{
	//Listener *RBClickListener = static_cast<Listener*>(m_tri);
	//RBClickListener->MouseRBDown(0, 0);

	return TRUE;
}
