#pragma once

#include "SlideBar.h"
#include "Vector2D.h"
#include "Renderable.h"
#include "Listener.h"

class _ColourSelect : public Renderable, public Listener
{
	private:
		Vector2D			areaTopLeft, areaTopRight, areaBottomLeft, areaBottomRight; 

		float				m_tlX, m_tlY, m_trX, m_trY, m_blX, m_blY, m_brX, m_brY;

		float				oldX, oldY;
		SlideBar			*topBarRed, *topBarGreen, *topBarBlue;  //The three colour slideBars

		float				tab1TLX, tab1TLY, tab1TRX, tab1TRY, tab1BLX, tab1BLY, tab1BRX, tab1BRY;
		float				tab2TLX, tab2TLY, tab2TRX, tab2TRY, tab2BLX, tab2BLY, tab2BRX, tab2BRY;
		float				tab3TLX, tab3TLY, tab3TRX, tab3TRY, tab3BLX, tab3BLY, tab3BRX, tab3BRY;
			
		float				applyBtnTLX, applyBtnTLY, applyBtnTRX, applyBtnTRY, 
							applyBtnBLX, applyBtnBLY, applyBtnBRX, applyBtnBRY;

		float				light = 1.0f, dark = 0.2f;
		float				alpha = 1.0f;

	public:
		bool				tab1Focus = true, tab2Focus = false, tab3Focus = false; //Tab1Focus starts as true, because that is focused on creation

		float				topBarRedf = 0.0f, topBarGreenf = 0.0f, topBarBluef = 133;
		float				startbarRed = 153.0f, startbarGreen = 153.0f, startbarBlue = 153.0f;
		float				desktopRed = 77.0f, desktopGreen = 153.0f, desktopBlue = 153.0f;
					
							_ColourSelect(float tlX, float tlY, float trX, float trY, float blX, float blY, float brX, float brY);
							~_ColourSelect();

		void				SetAlpha(float _alpha);
		void				SetAreaXY(float tlX, float tlY, float trX, float trY, float blX, float blY, float brX, float brY);
		void				RenderColourQuad();
		void				RenderWorkArea();
		void				RenderTabs();
		void				RenderButtons();
		void				RenderTabLabels();

		void				Render();
		bool				MouseMove(int x, int y);
		bool				MouseLBUp(int x, int y);
		bool				MouseLBDown(int x, int y);
		bool				MouseRBDown(int x, int y);
};