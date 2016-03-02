#include "ColourSelect.h"
#include <Windows.h>
#include <gl/GL.h>
#include "OGLWindowMaker.h"
#include "GLFont.h"
#include "freeglut.h"

_ColourSelect::_ColourSelect(float tlX, float tlY, float trX, float trY, float blX, float blY, float brX, float brY)
{
	//areaTopLeft, areaTopRight, areaBottomLeft, areaBottomRight
	areaTopLeft.SetX(tlX + 10.0f), areaTopLeft.SetY(tlY - 10.0f), areaTopRight.SetX(trX - 10.0f), areaTopRight.SetY(trY - 10.0f);
	areaBottomLeft.SetX(blX + 10.0f), areaBottomLeft.SetY(blY + 10.0f), areaBottomRight.SetX(brX - 10.0f), areaBottomRight.SetY(brY + 10.0f);

	topBarRed = new SlideBar("Red", 0.0f, 255.0f, tlX + 50, tlY + 100);
	topBarGreen = new SlideBar("Green", 0.0f, 255.0f, tlX + 50, tlY + 170);
	topBarBlue = new SlideBar("Blue", 0.0f, 255.0f, tlX + 50, tlY + 240);
}

_ColourSelect::~_ColourSelect()
{
	
}

void _ColourSelect::SetAlpha(float _alpha)
{
	alpha = _alpha;
}

void _ColourSelect::SetAreaXY(float tlX, float tlY, float trX, float trY, float blX, float blY, float brX, float brY)
{
	//Allows movement from outside the class
	m_tlX = tlX + 10.0f, m_tlY = tlY - 10.0f;
	m_trX = trX - 10.0f, m_trY = trY - 10.0f;
	m_blX = blX + 10.0f, m_blY = blY + 10.0f;
	m_brX = brX - 10.0f, m_brY = brY + 10.0f;
}

void _ColourSelect::RenderColourQuad()
{
	float topBarRedValue = (topBarRed->ReturnValue() / 255);
	float topBarGreenValue = (topBarGreen->ReturnValue() / 255);
	float topBarBlueValue = (topBarBlue->ReturnValue() / 255);

	//anchored to the corners to allow responsive resizing 
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
		glColor4f(topBarRedValue, topBarGreenValue, topBarBlueValue, alpha);
			glVertex2f(m_blX + 325.0f, m_trY - 35.0f);
			glVertex2f(m_blX + 325.0f, m_blY + 70.0f);
			glVertex2f(m_brX - 10.0f, m_blY + 70.0f);
			glVertex2f(m_brX - 10.0f, m_trY - 35.0f);
	glEnd();
}

void _ColourSelect::RenderWorkArea()
{
	glBegin(GL_LINES);
	{
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(m_tlX, m_tlY - 20.0f);
			glVertex2f(m_blX, m_blY + 40.0f);

		glColor4f(0.2f, 0.2f, 0.2f, alpha);
			glVertex2f(m_blX, m_blY + 40.0f);
			glVertex2f(m_brX, m_brY + 40.0f);

			glVertex2f(m_brX, m_brY + 40.0f);
			glVertex2f(m_trX, m_trY - 20.0f);

		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(m_trX, m_trY - 20.0f);
			glVertex2f(m_tlX, m_tlY - 20.0f);
	}
	glEnd();
}

void _ColourSelect::RenderTabs()
{
	tab1TLX = m_tlX + 2.0f, tab1TLY = m_tlY;
	tab1TRX = m_tlX + 80.0f, tab1TRY = m_tlY;
	tab1BLX = m_tlX + 2.0f, tab1BLY = m_tlY - 21.0f; 
	tab1BRX = m_tlX + 80.0f, tab1BRY = m_tlY - 21.0f;

	//Renders the clickable selection tabs
	glBegin(GL_QUADS);
		glColor4f((190 / 255.0f), (190 / 255.0f), (194 / 255.0f), alpha);
			glVertex2f(tab1TLX, tab1TLY);
			glVertex2f(tab1BLX, tab1BLY);
			glVertex2f(tab1BRX, tab1BRY);
			glVertex2f(tab1TRX, tab1TRY);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(tab1TRX, tab1TRY);
			glVertex2f(tab1TLX, tab1TLY);

			glVertex2f(tab1TLX, tab1TLY);
			glVertex2f(tab1BLX, tab1BLY - 1.0f);

			glVertex2f(tab1BRX, tab1BRY);
			glVertex2f(tab1TRX, tab1TRY);
	glEnd();

	tab2TLX = tab1TRX, tab2TLY = tab1TRY;
	tab2TRX = tab1TRX + 80.0f, tab2TRY = tab1TRY;
	tab2BLX = tab1TRX, tab2BLY = tab1BLY;
	tab2BRX = tab1BRX + 80.0f, tab2BRY = tab1BRY;

	glBegin(GL_QUADS);
		glColor4f((190 / 255.0f), (190 / 255.0f), (194 / 255.0f), alpha);
			glVertex2f(tab2TLX, tab2TLY);
			glVertex2f(tab2BLX, tab2BLY);
			glVertex2f(tab2BRX, tab2BRY);
			glVertex2f(tab2TRX, tab2TRY);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(tab2TRX, tab2TRY);
			glVertex2f(tab2TLX, tab2TLY);

			glVertex2f(tab2TLX, tab2TLY);
			glVertex2f(tab2BLX, tab2BLY - 1.0f);

			glVertex2f(tab2BRX, tab2BRY);
			glVertex2f(tab2TRX, tab2TRY);
	glEnd();

	tab3TLX = tab2TRX, tab3TLY = tab2TRY;
	tab3TRX = tab2TRX + 80.0f, tab3TRY = tab2TRY;
	tab3BLX = tab2TRX, tab3BLY = tab2BLY;
	tab3BRX = tab2BRX + 80.0f, tab3BRY = tab2BRY;

	glBegin(GL_QUADS);
		glColor4f((190 / 255.0f), (190 / 255.0f), (194 / 255.0f), alpha);
			glVertex2f(tab3TLX, tab3TLY);
			glVertex2f(tab3BLX, tab3BLY);
			glVertex2f(tab3BRX, tab3BRY);
			glVertex2f(tab3TRX, tab3TRY);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(tab3TRX, tab3TRY);
			glVertex2f(tab3TLX, tab3TLY);

			glVertex2f(tab3TLX, tab3TLY);
			glVertex2f(tab3BLX, tab3BLY - 1.0f);

			glVertex2f(tab3BRX, tab3BRY);
			glVertex2f(tab3TRX, tab3TRY);
	glEnd();

	//Puts in the "focus line"
	glBegin(GL_LINES);
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
			if (tab1Focus)
			{
				glEnable(GL_BLEND);
				glVertex2f(tab1BRX, tab1BRY);
				glVertex2f(tab1TRX, tab1TRY);
			}
			else
			{
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, alpha);
				glVertex2f(tab1BLX, tab1BLY + 1.0f);
				glVertex2f(tab1BRX, tab1BRY + 1.0f);
			}

		glColor4f(0.0f, 0.0f, 0.0f, alpha);
			if (tab2Focus)
			{
				glEnable(GL_BLEND);
				glVertex2f(tab2BRX, tab2BRY);
				glVertex2f(tab2TRX, tab2TRY);
			}
			else
			{
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, alpha);
				glVertex2f(tab2BLX, tab2BLY + 1.0f);
				glVertex2f(tab2BRX, tab2BRY + 1.0f);
			}

		glColor4f(0.0f, 0.0f, 0.0f, alpha);
			if (tab3Focus)
			{
				glEnable(GL_BLEND);
				glVertex2f(tab3BRX, tab3BRY);
				glVertex2f(tab3TRX, tab3TRY);
			}
			else
			{
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, alpha);
				glVertex2f(tab3BLX, tab3BLY + 1.0f);
				glVertex2f(tab3BRX, tab3BRY + 1.0f);
			}
	glEnd();
}

void _ColourSelect::RenderButtons()
{
	applyBtnTLX = m_brX - 80.0f, applyBtnTLY = m_brY + 30.0f;
	applyBtnBLX = m_brX - 80.0f, applyBtnBLY = m_brY;
	applyBtnBRX = m_brX - 10.0f, applyBtnBRY = m_brY;
	applyBtnTRX = m_brX - 10.0f, applyBtnTRY = m_brY + 30.0f; 

	//Apply button 
	glBegin(GL_QUADS);
		glColor4f((190 / 255.0f), (190 / 255.0f), (194 / 255.0f), alpha);
			glVertex2f(applyBtnTLX, applyBtnTLY);
			glVertex2f(applyBtnBLX, applyBtnBLY);
			glVertex2f(applyBtnBRX, applyBtnBRY);
			glVertex2f(applyBtnTRX, applyBtnTRY);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(dark, dark, dark, alpha);
			glVertex2f(applyBtnTRX, applyBtnTRY);
			glVertex2f(applyBtnBRX, applyBtnBRY);

			glVertex2f(applyBtnBRX + 1.0f, applyBtnBRY);
			glVertex2f(applyBtnBLX, applyBtnBLY);

		glColor4f(light, light, light, alpha);
			glVertex2f(applyBtnBLX, applyBtnBLY);
			glVertex2f(applyBtnTLX, applyBtnTLY);

			glVertex2f(applyBtnTLX, applyBtnTLY);
			glVertex2f(applyBtnTRX, applyBtnTRY);
	glEnd();

	GLFont *ApplyBtn = new GLFont();
	ApplyBtn->Create("franklin_gothic.glf");
		ApplyBtn->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
		ApplyBtn->RenderText("Apply", applyBtnTLX + 16.0f, applyBtnTLY - 7.0f, 0, 6.0f);
	ApplyBtn->End();
	delete ApplyBtn;
}

void _ColourSelect::RenderTabLabels()
{
	//Text for the tabs 
	GLFont *TopBarLabel = new GLFont();
	TopBarLabel->Create("another_font.glf");
		TopBarLabel->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
		TopBarLabel->RenderText("Top Bar", tab1TLX + 7.0f, tab1TLY - 2.0f, 0, 6.0f);
	TopBarLabel->End();
	delete TopBarLabel;

	GLFont *BackgroundLabel = new GLFont();
	BackgroundLabel->Create("another_font.glf");
		BackgroundLabel->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
		BackgroundLabel->RenderText("Desktop", tab2TLX + 7.0f, tab2TLY - 2.0f, 0, 6.0f);
	BackgroundLabel->End();
	delete BackgroundLabel;

	GLFont *StartBarLabel = new GLFont();
	StartBarLabel->Create("another_font.glf");
		StartBarLabel->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
		StartBarLabel->RenderText("Start Bar", tab3TLX + 7.0f, tab3TLY - 2.0f, 0, 6.0f);
	StartBarLabel->End();
	delete StartBarLabel;
}

void _ColourSelect::Render()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	RenderWorkArea();
	RenderTabs();
	RenderTabLabels();

	topBarRed->SetXY(m_tlX + 40.0f, m_tlY - 80.0f);
		topBarRed->Render();
	topBarGreen->SetXY(m_tlX + 40.0f, m_tlY - 150.0f);
		topBarGreen->Render();
	topBarBlue->SetXY(m_tlX + 40.0f, m_tlY - 220.0f);
		topBarBlue->Render();	

	glEnable(GL_BLEND);
	RenderButtons();

	topBarRed->SetAlpha(alpha);
	topBarGreen->SetAlpha(alpha);
	topBarBlue->SetAlpha(alpha);
	RenderColourQuad();

}

bool _ColourSelect::MouseMove(int x, int y)
{
	Listener *MouseMoveRedTopBarSlider = static_cast<Listener*>(topBarRed);
		MouseMoveRedTopBarSlider->MouseMove(x - oldX, y);
	Listener *MouseMoveGreenTopBarSlider = static_cast<Listener*>(topBarGreen);
		MouseMoveGreenTopBarSlider->MouseMove(x - oldX, y);
	Listener *MouseMoveBlueTopBarSlider = static_cast<Listener*>(topBarBlue);
		MouseMoveBlueTopBarSlider->MouseMove(x - oldX, y);

	oldX = x;
	oldY = y;

	return true;
}

bool _ColourSelect::MouseLBUp(int x, int y)
{
	light = 1.0f;
	dark = 0.2f;

	Listener *LBURedTopBarSlider = static_cast<Listener*>(topBarRed);
		LBURedTopBarSlider->MouseLBUp(x, y);
	Listener *LBUGreenTopBarSlider = static_cast<Listener*>(topBarGreen);
		LBUGreenTopBarSlider->MouseLBUp(x, y);
	Listener *LBUBlueTopBarSlider = static_cast<Listener*>(topBarBlue);
		LBUBlueTopBarSlider->MouseLBUp(x, y);

	if (x > applyBtnTLX && x < applyBtnTRX && y < applyBtnTLY && y > applyBtnBLY)
	{
		//Applied the colour changes depending on which tab index is selected 
		if (tab1Focus)
		{
			topBarRedf = topBarRed->ReturnValue();
			topBarGreenf = topBarGreen->ReturnValue();
			topBarBluef = topBarBlue->ReturnValue();
			return true;
		}

		if (tab2Focus)
		{
			desktopRed = topBarRed->ReturnValue();
			desktopGreen = topBarGreen->ReturnValue();
			desktopBlue = topBarBlue->ReturnValue();
			return true;
		}

		if (tab3Focus)
		{
			startbarRed = topBarRed->ReturnValue();
			startbarGreen = topBarGreen->ReturnValue();
			startbarBlue = topBarBlue->ReturnValue();
			return true;
		}
		return false;
	}
	return false;
}

bool _ColourSelect::MouseLBDown(int x, int y)
{
	oldX = x; 
	oldY = y;
	
	Listener *LBDRedTopBarSlider = static_cast<Listener*>(topBarRed);
		LBDRedTopBarSlider->MouseLBDown(x, y);
	Listener *LBDGreenTopBarSlider = static_cast<Listener*>(topBarGreen);
		LBDGreenTopBarSlider->MouseLBDown(x, y);
	Listener *LBDBlueTopBarSlider = static_cast<Listener*>(topBarBlue);
		LBDBlueTopBarSlider->MouseLBDown(x, y);

	if (x > tab1TLX && x < tab1TRX && y < tab1TLY && y > tab1BLY)
	{
		tab1Focus = true;
		tab2Focus = false; 
		tab3Focus = false; 
		return true;
	}

	if (x > tab2TLX && x < tab2TRX && y < tab2TLY && y > tab2BLY)
	{
		tab1Focus = false;
		tab2Focus = true;
		tab3Focus = false;
		return true;
	}

	if (x > tab3TLX && x < tab3TRX && y < tab3TLY && y > tab3BLY)
	{
		tab1Focus = false;
		tab2Focus = false;
		tab3Focus = true;
		return true;

	}

	if (x > applyBtnTLX && x < applyBtnTRX && y < applyBtnTLY && y > applyBtnBLY)
	{
		dark = 1.0f; 
		light = 0.2f;
		return true;

	}
	return false;
}

bool _ColourSelect::MouseRBDown(int x, int y)
{
	return true;
}
