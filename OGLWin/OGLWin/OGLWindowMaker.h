#pragma once

#include "Listener.h"
#include "Vector2D.h"
#include "Renderable.h"
#include "OGLStartBar.h"
#include "ColourSelect.h"
#include "PhotoView.h"

class OGLWindowMaker : public Renderable, public Listener
{
	private:
		Vector2D			m_topleft, m_topright;
		Vector2D			m_bottomleft, m_bottomright;

		const char*			WindowName;

		//for making button shadow colours
		float				closeTop = 0.3f, closeBottom = 1.0f;
		float				maxTop = 0.3f, maxBottom = 1.0f;
		float				minTop = 0.3f, minBottom = 1.0f;

		float				trX, trY, brX, brY, blX, blY, tlX, tlY; 	//main window points
		float				tb_trX, tb_trY, tb_brX, tb_brY, tb_blX, tb_blY, tb_tlX, tb_tlY; 	//top bar points

		//the main usable window body points
		float				main_trX, main_trY, main_brX, main_brY, main_blX, main_blY, main_tlX, main_tlY;
		float				cb_trX, cb_trY, cb_brX, cb_brY, cb_blX, cb_blY, cb_tlX, cb_tlY;
		float				maxb_trX, maxb_trY, maxb_brX, maxb_brY, maxb_blX, maxb_blY, maxb_tlX, maxb_tlY;
		float				minb_trX, minb_trY, minb_brX, minb_brY, minb_blX, minb_blY, minb_tlX, minb_tlY;

		float				oldX = 0, oldY = 0;
		float				alpha = 1.0f;
		bool				topBarClicked; 
		bool				resizeCornerClicked; 
		bool				windowMaxed = false;
		bool				minimiseAnimationActive = false; 

		float				old_tlX, old_tlY, old_trX, old_trY, 
							old_blX, old_blY, old_brX, old_brY;

		float				topBarFocusedRed = 0, topBarFocusedGreen = 0, topBarFocusedBlue = (185 / 255.0f); 	//Colour of the windows top bar when in focus
		float				topBarNotFocusedRed = 0.2f, topBarNotFocusedGreen = 0.2f, topBarNotFocusedBlue = 0.2f; 	//unfocused colour 
		float				minBRX, minBRY;		//Determines the minimum windows size. This is decided by the window type and will be set in the constructor

	public:
		_ColourSelect		*colourSelectWindow = new _ColourSelect(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		PhotoView			*photoViewWindow = new PhotoView();

		bool				MouseDown;
		bool				close = true;

		bool				Focused;

		float				topBarRed = 0, topBarGreen = 0, topBarBlue = 133;
		float				startbarRed = 153.0f, startbarGreen = 153.0f, startbarBlue = 153.0f;
		float				desktopRed = 77.0f, desktopGreen = 153.0f, desktopBlue = 153.0f;

		//Selected enums for windows types
		enum windowType {
			ColourSelect, PhotoViewer
		};
		windowType			typeOfWindow; //the windowtype variable that can be set to 
										 //a window type enum

							OGLWindowMaker(const char * windowName, float x, float y, enum windowType);

							~OGLWindowMaker();

		void				MaxButtonRender(float maxTop, float maxBottom);
		void				SetTopBarFocused(bool focused);
		void				MinButtonRender(float minTop, float maxTop);
		void				CloseButtonRender(float closeTop, float closeBottom);
		void				Render();
		void				SetTopBarColour(float red, float green, float blue);
		void				WindowMaximiser();
		void				WindowMinimiser();
		bool				MouseMove(int x, int y);
		bool				closeWindow();
		void				openWindow(bool open);
		bool				MouseLBUp(int x, int y);
		bool				MouseLBDown(int x, int y);
		bool				MouseRBDown(int x, int y);
};
