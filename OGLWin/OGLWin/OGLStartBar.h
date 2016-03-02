#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "Vector2D.h"
#include "OGLWindowMaker.h"

class OGLStartBar : public Renderable, public Listener
{
	private:
		Vector2D				m_startbtntopleft, m_startbtntopright;
		Vector2D				m_startbtnbottomright, m_startbtnbottomleft;

		Vector2D				m_topleft, m_topright;
		Vector2D				m_bottomleft, m_bottomright;

		Vector2D				menu_topleft, menu_topright;
		Vector2D				menu_bottomleft, menu_bottomright;

		Vector2D				windowTab1_topLeft, windowTab1_topRight;
		Vector2D				windowTab1_bottomLeft, windowTab1_bottomRight;
		Vector2D				windowTab2_topLeft, windowTab2_topRight;
		Vector2D				windowTab2_bottomLeft, windowTab2_bottomRight;
		Vector2D				windowTab3_topLeft, windowTab3_topRight;
		Vector2D				windowTab3_bottomLeft, windowTab3_bottomRight;

		bool					windowTab1Taken;
		bool					windowTab2Taken; 

		float					topShadow = 1.0f; 
		float					bottomShadow = 0.3f;
			
		int						hour, min, second;
		int						day, month, year;
		int						dateNumber;
		char*					amOrPM;
		char*					c_Day;
		char*					c_Month;

		float					timeOverx, timeOvery; 
			
		float					tlX, tlY, blX, blY, brX, brY, trX, trY;

		float					sbtlX, sbtlY, sbblX, sbblY, sbbrX, sbbrY, sbtrX, sbtrY;

		float					menu_tlX, menu_tlY, menu_blX, menu_blY, menu_brX, menu_brY, menu_trX, menu_trY;

		float					wt1_tlx, wt1_tly, wt1_blx, wt1_bly, wt1_brx, wt1_bry, wt1_trx, wt1_try;
		float					wt2_tlx, wt2_tly, wt2_blx, wt2_bly, wt2_brx, wt2_bry, wt2_trx, wt2_try;

		bool					slotOneActive;
		bool					slotOneDrawer1Active;
		bool					slotOneDrawer2Active;
		bool					slotTwoActive;
		bool					slotThreeActive;

		float					startBarRed, startBarGreen, startBarBlue; 

		unsigned char*			buffer;
		int						sizeX, sizeY, bpp, nChannels;

	public:
		bool					startButtonActive = false;
		bool					mouseOverTime; 

								OGLStartBar();
								~OGLStartBar();

		void					RenderStartBar();
		void					RenderStartButton();
		void					Time();
		void					RenderStartMenu();
		void					RenderStartMenuTextures();
		void					RenderStartMenuSlots();
		void					RenderWindowTabs();
		void					Render();
		void					RenderTimeOver();
		void					SetBarColour(float red, float green, float blue);
		bool					MouseMove(int x, int y);
		bool					MouseLBUp(int x, int y);
		bool					MouseLBDown(int x, int y);
		bool					MouseRBDown(int x, int y);
};
