#include <Windows.h>
#include <gl/GL.h>
#include "OGLWindowMaker.h"
#include "GLFont.h"
#include "OGLWindow.h"
#include "freeglut.h"
#include <iostream>

RECT ClientSize; 

OGLWindowMaker::OGLWindowMaker(const char* windowName, float x, float y, windowType WindowType)
{
	WindowName = windowName;
	float		closeTop = 0.3f;
	float		closeBottom = 1.0f;
	float		maxTop = 0.3f;
	float		maxBottom = 1.0f;
	float		minTop = 0.3f;
	float		minBottom = 1.0f;

	typeOfWindow = WindowType; 
	m_topleft.SetX(x), m_topleft.SetY(y);

	//Uses the enum to know which window needs to be made, each different window has different starting sizes 
	if (typeOfWindow == ColourSelect)
	{
		m_topright.SetX(m_topleft.GetX() + 400.0f);
		m_bottomright.SetY(m_topleft.GetY() - 400.0f);
	}
	if (typeOfWindow == PhotoViewer)
	{
		m_topright.SetX(m_topleft.GetX() + 500.0f);
		m_bottomright.SetY(m_topleft.GetY() - 450.0f);
	}
	m_topright.SetY(m_topleft.GetY());
	m_bottomright.SetX(m_topright.GetX());
	m_bottomleft.SetX(m_topleft.GetX()), m_bottomleft.SetY(m_bottomright.GetY());
}

OGLWindowMaker::~OGLWindowMaker()
{
}

RECT OGLWindow::WindowSize2(RECT* windowSize)
{
	ClientSize = *windowSize;

	return ClientSize;
}

void OGLWindowMaker::CloseButtonRender(float closeLight, float closeDark)
{
	//Makes the close button
	glBegin(GL_QUADS);
		glColor4f((153 / 255.0f), (153 / 255.0f), (153 / 255.0f), alpha);
			glVertex2f(cb_tlX, cb_tlY);
			glVertex2f(cb_blX, cb_blY);
			glVertex2f(cb_brX, cb_brY);
			glVertex2f(cb_trX, cb_trY);
	glEnd();

	//Adds shadow to button 
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor4f(closeDark, closeDark, closeDark, alpha);
			glVertex2f(cb_trX, cb_trY);
			glVertex2f(cb_tlX, cb_tlY);

			glVertex2f(cb_tlX + 1, cb_tlY - 1);
			glVertex2f(cb_blX + 1, cb_blY);

		glColor4f(closeLight, closeLight, closeLight, alpha);
			glVertex2f(cb_blX + 1, cb_blY);
			glVertex2f(cb_brX, cb_brY);

			glVertex2f(cb_brX, cb_brY);
			glVertex2f(cb_trX, cb_trY);
	glEnd();

	//Makes the cross
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
		glVertex2f(cb_blX + 4, cb_blY + 3);
		glVertex2f(cb_trX - 4, cb_trY - 4);

		glVertex2f(cb_tlX + 4, cb_tlY - 4);
		glVertex2f(cb_brX - 4, cb_brY + 3);
	glEnd();
}

void OGLWindowMaker::MaxButtonRender(float maxTop, float maxBottom)
{
	//maximise button
	glBegin(GL_QUADS);
		glColor4f((153 / 255.0f), (153 / 255.0f), (153 / 255.0f), alpha);
			glVertex2f(maxb_tlX, maxb_tlY);
			glVertex2f(maxb_blX, maxb_blY);
			glVertex2f(maxb_brX, maxb_brY);
			glVertex2f(maxb_trX, maxb_trY);
	glEnd();

	//button shadow
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor4f(maxBottom, maxBottom, maxBottom, alpha);
			glVertex2f(maxb_trX, maxb_trY);
			glVertex2f(maxb_tlX, maxb_tlY);

			glVertex2f(maxb_tlX + 1, maxb_tlY - 1);
			glVertex2f(maxb_blX + 1, maxb_blY);

		glColor4f(maxTop, maxTop, maxTop, alpha);
			glVertex2f(maxb_blX + 1, maxb_blY);
			glVertex2f(maxb_brX, maxb_brY);

			glVertex2f(maxb_brX, maxb_brY);
			glVertex2f(maxb_trX, maxb_trY);
	glEnd();

	//Makes maximise icon
	glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
			glVertex2f(maxb_tlX + 4, maxb_tlY - 4);
			glVertex2f(maxb_blX + 3, maxb_blY + 3);
			glVertex2f(maxb_brX - 3, maxb_brY + 3);
			glVertex2f(maxb_trX - 3, maxb_trY - 4);
	glEnd();

	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glVertex2f(maxb_tlX + 4, maxb_tlY - 4);
		glVertex2f(maxb_trX - 3, maxb_trY - 4);
	glEnd();
}

void OGLWindowMaker::SetTopBarFocused(bool focused)
{
	Focused = (focused) ? true : false;
}

void OGLWindowMaker::MinButtonRender(float minTop, float maxTop)
{
	//minimise button 
	glBegin(GL_QUADS);
		glColor4f((153 / 255.0f), (153 / 255.0f), (153 / 255.0f), alpha);
			glVertex2f(minb_tlX, minb_tlY);
			glVertex2f(minb_blX, minb_blY);
			glVertex2f(minb_brX, minb_brY);
			glVertex2f(minb_trX, minb_trY);
	glEnd();

	//button shadow
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor4f(minBottom, minBottom, minBottom, alpha);
			glVertex2f(minb_trX, minb_trY);
			glVertex2f(minb_tlX, minb_tlY);

			glVertex2f(minb_tlX + 1, minb_tlY - 1);
			glVertex2f(minb_blX + 1, minb_blY);

		glColor4f(minTop, minTop, minTop, alpha);
			glVertex2f(minb_blX + 1, minb_blY);
			glVertex2f(minb_brX, minb_brY);

			glVertex2f(minb_brX, minb_brY);
			glVertex2f(minb_trX, minb_trY);
	glEnd();

	//minimise icon
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
			glVertex2f(minb_blX + 4, minb_blY + 4);
			glVertex2f(minb_brX - 3, minb_brY + 4);
	glEnd();
}

void OGLWindowMaker::Render()
{
	if (typeOfWindow == ColourSelect)
	{
		topBarRed = colourSelectWindow->topBarRedf;
		topBarGreen = colourSelectWindow->topBarGreenf;
		topBarBlue = colourSelectWindow->topBarBluef;

		startbarRed = colourSelectWindow->startbarRed; 
		startbarGreen = colourSelectWindow->startbarGreen;
		startbarBlue = colourSelectWindow->startbarBlue;

		desktopRed = colourSelectWindow->desktopRed;
		desktopGreen = colourSelectWindow->desktopGreen;
		desktopBlue = colourSelectWindow->desktopBlue; 

		colourSelectWindow->SetAlpha(alpha);
	}
	if (typeOfWindow == PhotoViewer)
	{
		photoViewWindow->setAlpha(alpha);
	}
	trX = m_topright.GetX(), trY = m_topright.GetY();
	brX = m_bottomright.GetX(), brY = m_bottomright.GetY();
	blX = m_bottomleft.GetX(), blY = m_bottomleft.GetY();
	tlX = m_topleft.GetX(), tlY = m_topleft.GetY();

	tb_trX = trX - 2.0f, tb_trY = trY - 2.0f;
	tb_brX = trX - 2.0f, tb_brY = trY - 25.0f;
	tb_blX = tlX + 2.0f, tb_blY = tlY - 25.0f;
	tb_tlX = tlX + 2.0f, tb_tlY = tlY - 2.0f;;

	main_trX = tb_brX, main_trY = tb_brY - 3.0f;
	main_brX = tb_brX, main_brY = brY + 3.0f;
	main_blX = tb_tlX, main_blY = blY + 3.0f;
	main_tlX = tb_blX, main_tlY = tb_blY - 3.0f;

	cb_trX = tb_trX - 5.0f, cb_trY = tb_trY - 5.0f;
	cb_brX = tb_trX - 5.0f, cb_brY = tb_trY - 19.0f;
	cb_blX = tb_trX - 20.0f, cb_blY = tb_trY - 19.0f;
	cb_tlX = tb_trX - 20.0f, cb_tlY = tb_trY - 5.0f;

	maxb_trX = cb_tlX - 5.0f, maxb_trY = cb_trY;
	maxb_brX = cb_tlX - 5.0f, maxb_brY = cb_blY;
	maxb_blX = cb_tlX - 20.0f, maxb_blY = cb_blY;
	maxb_tlX = cb_tlX - 20.0f, maxb_tlY = cb_trY;

	minb_trX = maxb_tlX - 5.0f, minb_trY = maxb_trY;
	minb_brX = maxb_tlX - 5.0f, minb_brY = maxb_blY;
	minb_blX = maxb_tlX - 20.0f, minb_blY = maxb_blY;
	minb_tlX = maxb_tlX - 20.0f , minb_tlY = maxb_trY;

	//Makes the main window
	glBegin(GL_QUADS);
	glColor4f((190 / 255.0f), (190 / 255.0f), (194 / 255.0f), alpha);
		glVertex2f(tlX, tlY);
		glVertex2f(blX, blY);
		glVertex2f(brX, brY);
		glVertex2f(trX, trY);
	glEnd();

	//Renders the windows shadow
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(trX, trY + 1.0f);
			glVertex2f(tlX - 1.0f, tlY + 1.0f);

			glVertex2f(tlX - 1.0f, tlY + 1.0f);
			glVertex2f(tlX - 1.0f, blY - 1.0f);

			glColor4f(0.1f, 0.1f, 0.1f, alpha);
			glVertex2f(tlX, blY - 1.0f);
			glVertex2f(brX + 2.0f, blY - 1.0f);

			glVertex2f(brX + 1.0f, blY - 1.0f);
			glVertex2f(trX + 1.0f, trY);
	glEnd();
	//Makes the top bar
	glBegin(GL_QUADS);
		if (Focused)
		{
			glColor4f((topBarRed / 255.0f), (topBarGreen / 255.0f), (topBarBlue / 255.0f), alpha);
		}
		else
		{
			glColor4f(0.6f, 0.6f, 0.6f, alpha);
		}
			glVertex2f(tb_tlX, tb_tlY);
			glVertex2f(tb_blX, tb_blY);
			glVertex2f(tb_brX, tb_brY);
			glVertex2f(tb_trX, tb_trY);
	glEnd();

	CloseButtonRender(closeTop, closeBottom);
	MaxButtonRender(maxTop, maxBottom);
	MinButtonRender(minTop, minBottom);

	//Creates the main working window
	glBegin(GL_QUADS);
	glColor4f((190 / 255.0f), (190 / 255.0f), (194 / 255.0f), alpha);
	glVertex2f(main_tlX, main_tlY);
	glVertex2f(main_blX, main_blY);
	glVertex2f(main_brX, main_brY);
	glVertex2f(main_trX, main_trY);
	glEnd();

	if (windowMaxed && !minimiseAnimationActive)
	{
		WindowMaximiser();
	}

	if (minimiseAnimationActive)
	{
		WindowMinimiser();
	}
	//Creates window top bar text
	GLFont *pGLfont = new GLFont();
	pGLfont->Create("franklin_gothic.glf");
	pGLfont->Begin();

	Focused ? glColor4f(1.0f, 1.0f, 1.0f, alpha) : glColor4f(0.8f, 0.8f, 0.8f, alpha);

	if (typeOfWindow == PhotoViewer)
	{
		pGLfont->RenderText("Photo Viewer - Not implemented - Hit maximise though" , tb_tlX + 6, tb_tlY - 3, 0, 7);

	}
	else
	{
		pGLfont->RenderText(WindowName, tb_tlX + 6, tb_tlY - 3, 0, 7);
	}
	pGLfont->End();
	delete pGLfont;

	if (typeOfWindow == ColourSelect)
	{
		colourSelectWindow->SetAreaXY(main_tlX, main_tlY, main_trX, main_trY, main_blX, main_blY, main_brX, main_brY );
		colourSelectWindow->Render();
	}

	if (typeOfWindow == PhotoViewer)
	{
		photoViewWindow->setXY(main_tlX, main_tlY, main_trX, main_trY, main_blX, main_blY, main_brX, main_brY);
		photoViewWindow->Render();
	}
}

void OGLWindowMaker::SetTopBarColour(float red, float green, float blue)
{
	topBarRed = red; 
	topBarGreen = green; 
	topBarBlue = blue; 
}

void OGLWindowMaker::WindowMaximiser()
{
	//Not a great method for maximise animation
	if (m_topleft.GetX() >= (ClientSize.left - ClientSize.right) * 0.5)
	{		
		if (m_topleft.GetX() - 15.0f >= (ClientSize.left - ClientSize.right) * 0.5)
		{
			m_topleft.SetX(m_topleft.GetX() - 15.0f);
		}
		else
		{
			m_topleft.SetX((ClientSize.left - ClientSize.right) * 0.5);
		}
	}
	else
	{
		m_topleft.SetX((ClientSize.left - ClientSize.right) * 0.5);
	}
	if (m_topleft.GetY() <= (ClientSize.bottom - ClientSize.top) * 0.5)
	{
		if (m_topleft.GetY() + 15.0f <= (ClientSize.bottom - ClientSize.top) * 0.5)
		{
			m_topleft.SetY(m_topleft.GetY() + 15.0f);
		}
		else
		{
			m_topleft.SetY((ClientSize.bottom - ClientSize.top) * 0.5);
		}
	}
	else
	{
		m_topleft.SetY((ClientSize.bottom - ClientSize.top) * 0.5);
	}
	if (m_topright.GetX() <= (ClientSize.right - ClientSize.left) * 0.5)
	{
		if (m_topright.GetX() + 15.0f <= (ClientSize.right - ClientSize.left) * 0.5)
		{
			m_topright.SetX(m_topright.GetX() + 15.0f);
		}
		else
		{
			m_topright.SetX((ClientSize.right - ClientSize.left) * 0.5);
		}
	}
	else
	{
		m_topright.SetX((ClientSize.right - ClientSize.left) * 0.5);
	}
	if (m_topright.GetY() <= (ClientSize.bottom - ClientSize.top) * 0.5)
	{
		if (m_topright.GetY() + 15.0f <= (ClientSize.bottom - ClientSize.top) * 0.5)
		{
			m_topright.SetY(m_topright.GetY() + 15.0f);
		}
		else
		{
			m_topright.SetY((ClientSize.bottom - ClientSize.top) * 0.5);
		}
	}
	else
	{
		m_topright.SetY((ClientSize.bottom - ClientSize.top) * 0.5);
	}
	if (m_bottomleft.GetX() >= (ClientSize.left - ClientSize.right) * 0.5)
	{
		if (m_bottomleft.GetX() - 15.0f >= (ClientSize.left - ClientSize.right) * 0.5)
		{
			m_bottomleft.SetX(m_bottomleft.GetX() - 15.0f);
		}
		else
		{
			m_bottomleft.SetX((ClientSize.left - ClientSize.right) * 0.5);
		}
	}
	else
	{
		m_bottomleft.SetX((ClientSize.left - ClientSize.right) * 0.5);
	}
	if (m_bottomleft.GetY() >= (ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f)
	{
		if (m_bottomleft.GetY() - 15.0f >= (ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f)
		{
			m_bottomleft.SetY(m_bottomleft.GetY() - 15.0f);
		}
		else
		{
			m_bottomleft.SetY((ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f);
		}
	}
	else
	{
		m_bottomleft.SetY((ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f);
	}
	if (m_bottomright.GetX() < (ClientSize.right - ClientSize.left) * 0.5)
	{
		if (m_bottomright.GetX() + 15.0f <= (ClientSize.right - ClientSize.left) * 0.5)
		{
			m_bottomright.SetX(m_bottomright.GetX() + 15.0f);
		}
		else
		{
			m_bottomright.SetX((ClientSize.right - ClientSize.left) * 0.5);
		}
	}
	else
	{
		m_bottomright.SetX((ClientSize.right - ClientSize.left) * 0.5);
	}
	if (m_bottomright.GetY() >= (ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f)
	{
		if (m_bottomright.GetY() - 15.0f >= (ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f)
		{
			m_bottomright.SetY(m_bottomright.GetY() - 15.0f);
		}
		else
		{
			m_bottomright.SetY((ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f);
		}
	}
	else
	{
		m_bottomright.SetY((ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f);
	}
	//The ugliest if statement ever known - It checks if all of the requirements are met - If they are, it changes the alpha back to normal 
	if (m_topleft.GetX() == (ClientSize.left - ClientSize.right) * 0.5 && m_topleft.GetY() == (ClientSize.bottom - ClientSize.top) * 0.5 &&
		m_topright.GetX() == (ClientSize.right - ClientSize.left) * 0.5 && m_topright.GetY() == (ClientSize.bottom - ClientSize.top) * 0.5 &&
		m_bottomleft.GetX() == (ClientSize.left - ClientSize.right) * 0.5 && m_bottomleft.GetY() == (ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f &&
		m_bottomright.GetX() == (ClientSize.right - ClientSize.left) * 0.5 && m_bottomright.GetY() == (ClientSize.top - ClientSize.bottom) * 0.5 + 31.0f)
	{
		alpha = 1.0f; 
	}
}

void OGLWindowMaker::WindowMinimiser()
{

	if (m_topleft.GetX() <= old_tlX)
	{
		if (m_topleft.GetX() + 15.0f >= old_tlX)
		{
			m_topleft.SetX(old_tlX);
		}
		else
		{
			m_topleft.SetX(m_topleft.GetX() + 15.0f);
		}
	}
	else
	{
		m_topleft.SetX(old_tlX);
	}
	if (m_topleft.GetY() >= old_tlY)
	{
		if (m_topleft.GetY() - 15.0f <= old_tlY)
		{
			m_topleft.SetY(old_tlY);
		}
		else
		{
			m_topleft.SetY(m_topleft.GetY() - 15.0f);
		}
	}
	else
	{
		m_topleft.SetY(old_tlY);
	}
	if (m_topright.GetX() >= old_trX)
	{
		if (m_topright.GetX() - 15.0f <= old_trX)
		{
			m_topright.SetX(old_trX);
		}
		else
		{
			m_topright.SetX(m_topright.GetX() - 15.0f);
		}
	}
	else
	{
		m_topright.SetX(old_trX);
	}
	if (m_topright.GetY() >= old_trY)
	{
		if (m_topright.GetY() - 15.0f <= old_trY)
		{
			m_topright.SetY(old_trY);
		}
		else
		{
			m_topright.SetY(m_topright.GetY() - 15.0f);
		}
	}
	else
	{
		m_topright.SetY(old_trY);
	}
	if (m_bottomleft.GetX() <= old_blX)
	{
		if (m_bottomleft.GetX() + 15.0f >= old_blX)
		{
			m_bottomleft.SetX(old_blX);
		}
		else
		{
			m_bottomleft.SetX(m_bottomleft.GetX() + 15.0f);
		}
	}
	else
	{
		m_bottomleft.SetX(old_blX);
	}
	if (m_bottomleft.GetY() <= old_blY)
	{
		if (m_bottomleft.GetY() + 15.0f >= old_blY)
		{
			m_bottomleft.SetY(old_blY);
		}
		else
		{
			m_bottomleft.SetY(m_bottomleft.GetY() + 15.0f);
		}
	}
	else
	{
		m_bottomleft.SetY(old_blY);
	}
	if (m_bottomright.GetX() >= old_brX)
	{
		if (m_bottomright.GetX() - 15.0f <= old_brX)
		{
			m_bottomright.SetX(old_brX);
		}
		else
		{
			m_bottomright.SetX(m_bottomright.GetX() - 15.0f);
		}
	}
	else
	{
		m_bottomright.SetX(old_brX);
	}
	if (m_bottomright.GetY() <= old_brY)
	{
		if (m_bottomright.GetY() + 15.0f >= old_brY)
		{
			m_bottomright.SetY(old_brY);
		}
		else
		{
			m_bottomright.SetY(m_bottomright.GetY() + 15.0f);
		}
	}
	else
	{
		m_bottomright.SetY(old_brY);
	}
	//When the requirement is met (they've returned to their original values), it will end the animation bool. 
	if (m_topleft.GetX() == old_tlX && m_topleft.GetY() == old_tlY && m_topright.GetX() == old_trX && m_topright.GetY() == old_trY &&
		m_bottomleft.GetX() == old_blX && m_bottomleft.GetY() == old_blY && m_bottomright.GetX() == old_brX && m_bottomright.GetY() == old_brY)
	{
		minimiseAnimationActive = false; 
		alpha = 1.0f;
	}
}

bool OGLWindowMaker::MouseMove(int x, int y)
{
	if (MouseDown)
	{
		if (topBarClicked)
		{
			if (!windowMaxed)
			{
				alpha = 0.5f;

				m_topleft.SetX(m_topleft.GetX() + (x - oldX));
				m_topleft.SetY(m_topleft.GetY() + (y - oldY));
				m_topright.SetX(m_topright.GetX() + (x - oldX));
				m_topright.SetY(m_topright.GetY() + (y - oldY));
				m_bottomright.SetX(m_bottomright.GetX() + (x - oldX));
				m_bottomright.SetY(m_bottomright.GetY() + (y - oldY));
				m_bottomleft.SetX(m_bottomleft.GetX() + (x - oldX));
				m_bottomleft.SetY(m_bottomleft.GetY() + (y - oldY));
			}
		}

		if (resizeCornerClicked)
		{
			alpha = 0.5f;

			if (typeOfWindow == ColourSelect)
			{
				if (m_bottomright.GetX() > (m_bottomleft.GetX() + 400.0f))
				{
					if (m_bottomright.GetY() < (m_topright.GetY() - 400.0f) && (m_bottomright.GetY() > ((float)ClientSize.top - (float)ClientSize.bottom) * 0.5 + 29.0f))
					{
						m_bottomright.SetX(m_bottomright.GetX() + (x - oldX));
						m_bottomright.SetY(m_bottomright.GetY() + (y - oldY));
						m_bottomleft.SetY(m_bottomleft.GetY() + (y - oldY));
						m_topright.SetX(m_topright.GetX() + (x - oldX));
					}
					else
					{
						m_bottomright.SetY(m_bottomright.GetY() - 1.0f);
						m_bottomleft.SetY(m_bottomleft.GetY() - 1.0f);
					}
				}
				else
				{
					m_bottomright.SetX(m_bottomright.GetX() + 1.0f);
					m_topright.SetX(m_topright.GetX() + 1.0f);
				}
			}

			if (typeOfWindow == PhotoViewer)
			{
				if (m_bottomright.GetX() > (m_bottomleft.GetX() + 500.0f))
				{
					if (m_bottomright.GetY() < (m_topright.GetY() - 450.0f) && (m_bottomright.GetY() > ((float)ClientSize.top - (float)ClientSize.bottom) * 0.5 + 29.0f))
					{
						m_bottomright.SetX(m_bottomright.GetX() + (x - oldX));
						m_bottomright.SetY(m_bottomright.GetY() + (y - oldY));
						m_bottomleft.SetY(m_bottomleft.GetY() + (y - oldY));
						m_topright.SetX(m_topright.GetX() + (x - oldX));
					}
					else
					{
						m_bottomright.SetY(m_bottomright.GetY() - 1.0f);
						m_bottomleft.SetY(m_bottomleft.GetY() - 1.0f);
					}
				}
				else
				{
					m_bottomright.SetX(m_bottomright.GetX() + 1.0f);
					m_topright.SetX(m_topright.GetX() + 1.0f);
				}
			}

			else if (m_bottomright.GetX() > (m_bottomleft.GetX() + 200.0f))
			{
				if (m_bottomright.GetY() < (m_topright.GetY() - 150.0f) && (m_bottomright.GetY() > ((float)ClientSize.top - (float)ClientSize.bottom) * 0.5 + 29.0f))
				{
					m_bottomright.SetX(m_bottomright.GetX() + (x - oldX));
					m_bottomright.SetY(m_bottomright.GetY() + (y - oldY));
					m_bottomleft.SetY(m_bottomleft.GetY() + (y - oldY));
					m_topright.SetX(m_topright.GetX() + (x - oldX));
				}
				else
				{
					m_bottomright.SetY(m_bottomright.GetY() - 1.0f);
					m_bottomleft.SetY(m_bottomleft.GetY() - 1.0f);
				}
			}
			else
			{
				m_bottomright.SetX(m_bottomright.GetX() + 1.0f);
				m_topright.SetX(m_topright.GetX() + 1.0f);
			}
		}
	}

	if (typeOfWindow == ColourSelect)
	{
		Listener *MouseMoveColourSelect = static_cast<Listener*>(colourSelectWindow);
		MouseMoveColourSelect->MouseMove(x, y);
	}

	//Saves the original x and y 
	oldX = x;
	oldY = y;
	return true;
}

bool OGLWindowMaker::closeWindow()
{
	return close;
}

void OGLWindowMaker::openWindow(bool open)
{
	close = open; 
}

bool OGLWindowMaker::MouseLBUp(int x, int y)
{
		MouseDown = false;
		topBarClicked = false;
		resizeCornerClicked = false;

		alpha = 1.0f;

		closeTop = 0.3f, closeBottom = 1.0f;
		maxTop = 0.3f, maxBottom = 1.0f;
		minTop = 0.3f, minBottom = 1.0f;

		if (x > tlX && x < trX && y < tlY && y > blY)
		{
			//if mouse is pulled up on close button
			if ((float)x > cb_tlX && (float)x < cb_trX && (float)y < cb_tlY && (float)y > cb_blY)
			{
				close = true;
			}

			//if mouse is pulled up on max button 
			if ((float)x > maxb_tlX && (float)x < maxb_trX && (float)y < maxb_tlY && (float)y > maxb_blY)
			{
				if (windowMaxed == false)
				{
					//Saves the original position of the window before manipulating any vectors
					old_tlX = m_topleft.GetX(), old_tlY = m_topleft.GetY();
					old_trX = m_topright.GetX(), old_trY = m_topright.GetY();
					old_blX = m_bottomleft.GetX(), old_blY = m_bottomleft.GetY();
					old_brX = m_bottomright.GetX(), old_brY = m_bottomright.GetY();
					alpha = 0.5f;
				}
				if (windowMaxed == true)
				{
					minimiseAnimationActive = true;
					alpha = 0.5f;
				}
				windowMaxed = windowMaxed ? false : true;
			}

			if (typeOfWindow == ColourSelect)
			{
				Listener *LBUColourSelect = static_cast<Listener*>(colourSelectWindow);
				LBUColourSelect->MouseLBUp(x, y);
			}
			return true;		
		}
		return false;
}

bool OGLWindowMaker::MouseLBDown(int x, int y)
{
	if (x > tlX && x < trX && y < tlY && y > blY)
	{
		//Resets the oldX/Y used in the old movement to the new click co-ordinates
		oldX = x;
		oldY = y;

		//mouse down on close button
		if ((float)x > cb_tlX && (float)x < cb_trX && (float)y < cb_tlY && (float)y > cb_blY)
		{
			MouseDown = true;

			closeTop = 1.0f;
			closeBottom = 0.3f;

			return true;
		}

		//mouse down on max button
		if ((float)x > maxb_tlX && (float)x < maxb_trX && (float)y < maxb_tlY && (float)y > maxb_blY)
		{
			MouseDown = true;

			maxTop = 1.0f;
			maxBottom = 0.3f;

			return true;
		}

		//If mouse down on min button
		if ((float)x > minb_tlX && (float)x < minb_trX && (float)y < minb_tlY && (float)y > minb_blY)
		{
			MouseDown = true;

			minTop = 1.0f;
			minBottom = 0.3f;

			return true;
		}

		//Mouse down on the top bar for moving
		if ((float)x > tb_tlX && (float)x < tb_trX && (float)y < tb_tlY && (float)y > tb_blY &&
			!((float)x > cb_tlX && !(float)x < cb_trX && !(float)y < cb_tlY && !(float)y > cb_blY))
		{
			MouseDown = true;
			topBarClicked = true;
			return true;
		}

		//mouse down in the bottom right corner for resizing
		if ((float)x > brX - 7 && (float)x < brX && (float)y < brY + 7 && (float)y > brY)
		{
			MouseDown = true;
			//If the window is maximised, it doesnt allow the bool to change.
			//so the window cannot be resized with in maxed mode
			if (windowMaxed == false)
			{
				resizeCornerClicked = true;
			}

			return true;
		}

		if (typeOfWindow == ColourSelect)
		{
			Listener *LBDColourSelect = static_cast<Listener*>(colourSelectWindow);
			LBDColourSelect->MouseLBDown(x, y);
		}
		return true;
	}
	else
	{
		return false;
	}
	
	return false; 
}

bool OGLWindowMaker::MouseRBDown(int x, int y)
{
	return true;

}

