#pragma once

#include <Windows.h>
#include "OGLWindowMaker.h"
#include "OGLStartBar.h"
#include "DesktopIcon.h"

class OGLWindow
{
	private:
			HWND		m_hwnd;				//handle to a window
			HDC			m_hdc;				//handle to a device context
			HGLRC		m_hglrc;			//handle to a gl rendering context 
			float		desktopRed = 77.0f, desktopGreen = 153.0f, desktopBlue = 153.0f; 

	protected:
			HGLRC		CreateOGLContext (HDC hdc);
			BOOL		DestroyOGLContext();
			BOOL		InitWindow(HINSTANCE hInstance, int width, int height);
			void		InitOGLState();

	public:			
			OGLWindowMaker		*photoViewer;
			OGLWindowMaker		*colourSelector;
			OGLStartBar			*m_startbar;
			DesktopIcon			*photoViewerIcon; 
			DesktopIcon			*colourSelectorIcon; 

			OGLWindowMaker*		render[3]; 
			Renderable*			renderWindow;
			Renderable*			renderWindow2;
			Renderable*			renderStartbar;

								OGLWindow();
								OGLWindow(HINSTANCE hInstance, int width, int height);
								~OGLWindow();

			int					m_width;
			int					m_height;

			void				SetDesktopColour(float red, float green, float blue);

			void				Render();
			void				Resize( int width, int height );
			void				SetVisible( BOOL visible );
			void				DestroyOGLWindow();

			BOOL				MouseLBDown ( int x, int y );
			BOOL				MouseLBUp ( int x, int y );
			BOOL				MouseMove ( int x, int y );
			BOOL				MouseRBDown(int x, int y);

			RECT				windowRect;
			RECT				WindowSize(RECT *windowSize);
			RECT				WindowSize2(RECT *windowSize);
};