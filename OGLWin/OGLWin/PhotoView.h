#pragma once

#include "SlideBar.h"
#include "Vector2D.h"
#include "Renderable.h"
#include "Listener.h"

class PhotoView : public Renderable, public Listener
{
	private:	
		float				m_tlX, m_tlY, m_trX, m_trY, m_blX, m_blY, m_brX, m_brY;

		float				alpha = 1.0f;

		Vector2D			photo_tl[20], photo_bl[20], photo_br[20], photo_tr[20];
		unsigned			int texture[1];

		char*				photos[20];
		
		unsigned char*		buffer;
		int					sizeX, sizeY, bpp, nChannels;

	public:
							PhotoView();
							~PhotoView();

		void				setXY(float tlX, float tlY, float trX, float trY, float blX, float blY, float brX, float brY);
		void				setAlpha(float _alpha);
		void				RenderViewArea();
		void				Render();
		void				RenderIconsQuads();
		bool				MouseMove(int x, int y);
		bool				MouseLBUp(int x, int y);
		bool				MouseLBDown(int x, int y);
		bool				MouseRBDown(int x, int y);
};

