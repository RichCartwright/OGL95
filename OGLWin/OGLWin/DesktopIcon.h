#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "Vector2D.h"

class DesktopIcon : public Renderable, public Listener
{
	private: 
		Vector2D			m_topleft, m_topright, m_bottomleft, m_bottomright; 
		float				tlX, tlY, trX, trY, blX, blY, brX, brY;

	public:
		//Enum which is to determine what window type it is
		enum iconType {
			PhotoViewer, ColourSelector
		};
		iconType			Icon_Type; 

							DesktopIcon(float x, float y, iconType IconType);
							~DesktopIcon();

		void				setXY(float x, float y);
		void				RenderIconQuad();
		void				Render();
		bool				MouseMove(int x, int y);
		bool				MouseLBUp(int x, int y);
		bool				MouseLBDown(int x, int y);
		bool				MouseRBDown(int x, int y);
};

