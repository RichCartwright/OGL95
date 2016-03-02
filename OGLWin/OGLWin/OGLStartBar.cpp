#include "OGLStartBar.h"
#include "OGLWindow.h"
#include "GLFont.h"
#include <Windows.h>
#include <gl/GL.h>
#include <sstream>
#include "freeglut.h"
#include "ImageReader.h"

RECT		m_windowSize;

OGLStartBar::OGLStartBar()
{
	float windowRight, windowBottom, windowTop, windowLeft;

	windowRight = m_windowSize.right, windowBottom = m_windowSize.bottom;
	windowTop = m_windowSize.top, windowLeft = m_windowSize.left;

	m_topleft.SetX((windowLeft - windowRight) * 0.5), m_topleft.SetY(((windowTop - windowBottom) + 56.0f) * 0.5);
	m_topright.SetX((windowRight - windowLeft) * 0.5), m_topright.SetY(((windowTop - windowBottom) + 56.0f) * 0.5);
	m_bottomleft.SetX((windowLeft - windowRight) * 0.5), m_bottomleft.SetY((windowTop - windowBottom) * 0.5);
	m_bottomright.SetX((windowRight - windowLeft) * 0.5), m_bottomright.SetY((windowTop - windowBottom) * 0.5);

	m_startbtntopleft.SetX((float)m_topleft.GetX() + 3.0f), m_startbtntopleft.SetY((float)m_topleft.GetY() - 4.0f);
	m_startbtntopright.SetX((float)m_topleft.GetX() + 65.0f), m_startbtntopright.SetY((float)m_topleft.GetY() - 4.0f);
	m_startbtnbottomright.SetX((float)m_topleft.GetX() + 65.0f), m_startbtnbottomright.SetY((float)m_topleft.GetY() - 26.0f);
	m_startbtnbottomleft.SetX((float)m_topleft.GetX() + 3.0f), m_startbtnbottomleft.SetY((float)m_topleft.GetY() - 26.0f);

	menu_topleft.SetX(m_startbtntopleft.GetX() + 1.0f), menu_topleft.SetY(m_topleft.GetY() + 300.0f);
	menu_topright.SetX(m_topleft.GetX() + 200.0f), menu_topright.SetY(m_topleft.GetY() + 300.0f);
	menu_bottomleft.SetX(m_startbtntopleft.GetX() + 1.0f), menu_bottomleft.SetY(m_startbtntopleft.GetY() + 2.0f);
	menu_bottomright.SetX(m_topleft.GetX() + 200.0f), menu_bottomright.SetY(m_startbtntopleft.GetY() + 2.0f);

	windowTab1_topLeft.SetX(m_startbtntopright.GetX() + 10.0f), windowTab1_topLeft.SetY(m_startbtntopright.GetY());
	windowTab1_topRight.SetX(windowTab1_topLeft.GetX() + 120.0f), windowTab1_topRight.SetY(windowTab1_topLeft.GetY());
	windowTab1_bottomLeft.SetX(windowTab1_topLeft.GetX()), windowTab1_bottomLeft.SetY(m_startbtnbottomleft.GetY());
	windowTab1_bottomRight.SetX(windowTab1_topRight.GetX()), windowTab1_bottomRight.SetY(windowTab1_bottomLeft.GetY());

	windowTab2_topLeft.SetX(windowTab1_topRight.GetX() + 5.0f), windowTab2_topLeft.SetY(m_startbtntopright.GetY());
	windowTab2_topRight.SetX(windowTab2_topLeft.GetX() + 120.0f), windowTab2_topRight.SetY(windowTab1_topLeft.GetY());
	windowTab2_bottomLeft.SetX(windowTab1_topRight.GetX() + 5.0f), windowTab2_bottomLeft.SetY(m_startbtnbottomleft.GetY());
	windowTab2_bottomRight.SetX(windowTab2_topLeft.GetX() + 120.0f), windowTab2_bottomRight.SetY(windowTab1_bottomLeft.GetY());
}

OGLStartBar::~OGLStartBar()
{

}

RECT OGLWindow::WindowSize(RECT* windowSize)
{
	m_windowSize = *windowSize;
	return m_windowSize;
}

void OGLStartBar::RenderStartBar()
{
	tlX = m_topleft.GetX(), tlY = m_topleft.GetY();
	blX = m_bottomleft.GetX(), blY = m_bottomleft.GetY();
	brX = m_bottomright.GetX(), brY = m_bottomright.GetY();
	trX = m_topright.GetX(), trY = m_topright.GetY();

	//Creates the whole startbar quad 
	glBegin(GL_QUADS);
		glColor3f((startBarRed / 255.0f), (startBarGreen / 255.0f), (startBarBlue / 255.0f));
			glVertex2f(tlX, tlY);
			glVertex2f(blX, blY);
			glVertex2f(brX, brY);
			glVertex2f(trX, trY);
	glEnd();

	//Adds the "shadow" lines
	glBegin(GL_LINES);
		glColor3f(0.9f, 0.9f, 0.9f);
			glVertex2d(trX, trY);
			glVertex2d(tlX, tlY);
	glEnd();
}

void OGLStartBar::RenderStartButton()
{
	sbtlX = m_startbtntopleft.GetX(), sbtlY = m_startbtntopleft.GetY();
	sbblX = m_startbtnbottomleft.GetX(), sbblY = m_startbtnbottomleft.GetY();
	sbbrX = m_startbtnbottomright.GetX(), sbbrY = m_startbtnbottomright.GetY();
	sbtrX = m_startbtntopright.GetX(), sbtrY = m_startbtntopright.GetY();
	//Renders the startbutton quad
	glBegin(GL_QUADS);
		glColor3f((startBarRed / 255.0f), (startBarGreen / 255.0f), (startBarBlue / 255.0f));
			glVertex2f(sbtlX, sbtlY);
			glVertex2f(sbblX, sbblY);
			glVertex2f(sbbrX, sbbrY);
			glVertex2f(sbtrX, sbtrY);
	glEnd();

	//Adds shadow lines
	glBegin(GL_LINES);
		glColor3f(topShadow, topShadow, topShadow);
			glVertex2d(sbtrX, sbtrY);
			glVertex2d(sbtlX, sbtlY);
			glVertex2d(sbtlX + 1, sbtlY - 1);
			glVertex2d(sbblX + 1, sbblY);

		glColor3f(bottomShadow, bottomShadow, bottomShadow);
			glVertex2d(sbblX + 1, sbblY);
			glVertex2d(sbbrX, sbbrY);
			glVertex2d(sbbrX, sbbrY);
			glVertex2d(sbtrX, sbtrY);
	glEnd();

	glBegin(GL_QUADS);
		//red
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glVertex2d(sbtlX + 6.0f, sbtlY - 5.0f);
			glVertex2d(sbtlX + 6.0f, sbtlY - 10.0f);
			glVertex2d(sbtlX + 11.0f, sbtlY - 10.0f);
			glVertex2d(sbtlX + 11.0f, sbtlY - 5.0f);
		//green
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			glVertex2d(sbtlX + 12.0f, sbtlY - 5.0f);
			glVertex2d(sbtlX + 12.0f, sbtlY - 10.0f);
			glVertex2d(sbtlX + 17.0f, sbtlY - 10.0f);
			glVertex2d(sbtlX + 17.0f, sbtlY - 5.0f);
		//blue
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			glVertex2d(sbtlX + 6.0f, sbtlY - 10.0f);
			glVertex2d(sbtlX + 6.0f, sbtlY - 16.0f);
			glVertex2d(sbtlX + 11.0f, sbtlY - 16.0f);
			glVertex2d(sbtlX + 11.0f, sbtlY - 11.0f);
		//yellow
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			glVertex2d(sbtlX + 12.0f, sbtlY - 11.0f);
			glVertex2d(sbtlX + 12.0f, sbtlY - 16.0f);
			glVertex2d(sbtlX + 17.0f, sbtlY - 16.0f);
			glVertex2d(sbtlX + 17.0f, sbtlY - 11.0f);
	glEnd();

	//Windows logo lines 
	glLineWidth(1.0f);
	glBegin(GL_LINES);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glVertex2d(sbtlX + 6.0f, sbtlY - 4.0f);
			glVertex2d(sbtlX + 6.0f, sbtlY - 17.0f);

			glVertex2d(sbtlX + 6.0f, sbtlY - 17.0f);
			glVertex2d(sbtlX + 18.0f, sbtlY - 16.0f);

			glVertex2d(sbtlX + 18.0f, sbtlY - 17.0f);
			glVertex2d(sbtlX + 18.0f, sbtlY - 4.0f);

			glVertex2d(sbtlX + 18.0f, sbtlY - 5.0f);
			glVertex2d(sbtlX + 6.0f, sbtlY - 4.0f);

			glVertex2d(sbtlX + 12.0f, sbtlY - 4.0f);
			glVertex2d(sbtlX + 12.0f, sbtlY - 16.0f);

			glVertex2d(sbtlX + 6.0f, sbtlY - 10.0f);
			glVertex2d(sbtlX + 18.0f, sbtlY - 11.0f);
	glEnd();

	//Start button text
	GLFont *startText = new GLFont();
		startText->Create("franklin_gothic.glf");
		startText->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		startText->RenderText("Start", sbtlX + 22, sbtlY - 1, 0, 7);
		startText->End();
	delete startText;
}

void OGLStartBar::Time()
{
	tlX = m_topleft.GetX(), tlY = m_topleft.GetY();
	blX = m_bottomleft.GetX(), blY = m_bottomleft.GetY();
	brX = m_bottomright.GetX(), brY = m_bottomright.GetY();
	trX = m_topright.GetX(), trY = m_topright.GetY();

	//Clock box 
	glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2d(brX - 3.0f, brY + 3.0f);
			glVertex2d(brX - 100.0f, brY + 3.0f);

		glColor3f(0.3f, 0.3f, 0.3f);
			glVertex2d(brX - 100.0f, brY + 3.0f);
			glVertex2d(brX - 100.0f, brY + 24.0f);
			glVertex2d(brX - 100.0f, brY + 24.0f);
			glVertex2d(brX - 3.0f, brY + 24.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2d(brX - 3.0f, brY + 24.0f);
			glVertex2d(brX - 3.0f, brY + 3.0f);
	glEnd();

	//System clock
	////Gets the system time
	SYSTEMTIME time;
	//Gets local time from the address of the system time
	GetLocalTime(&time);	
	//Casts the SYSTEMTIME into ints 
	hour = time.wHour, min = time.wMinute, second = time.wSecond;
	day = time.wDayOfWeek, month = time.wMonth, year = time.wYear;
	dateNumber = time.wDay;
	amOrPM = " AM", c_Day = "", c_Month = "";

	switch (day)
	{		
		case 0:			
			c_Day = "Sunday";
			break;
		case 1:
			c_Day = "Monday";
			break;
		case 2:
			c_Day = "Tuesday";
			break;
		case 3:
			c_Day = "Wednesday";
			break;
		case 4:
			c_Day = "Thursday";
			break;
		case 5:
			c_Day = "Friday";
			break;
		case 6:
			c_Day = "Saturday";
			break;
		default:
			c_Day = "Error";
			break;
	}

	switch (month)
	{
		case 1:
			c_Month = "January";
			break;
		case 2:
			c_Month = "Feburary";
			break;
		case 3:
			c_Month = "March";	
			break;
		case 4:
			c_Month = "April";
			break;
		case 5:
			c_Month = "May";
			break;
		case 6:
			c_Month = "June";
			break;
		case 7:
			c_Month = "July";
			break;
		case 8:
			c_Month = "August";
			break;
		case 9: 
			c_Month = "September";
			break;
		case 10:
			c_Month = "October";
			break;
		case 11:
			c_Month = "November";
			break;
		case 12:
			c_Month = "December";
			break;
		default:
			c_Month = "Error";
			break;
	}

	//If the hour is PM, it will take off 12 hours and change the char pointer to PM
	if (hour > 12)
	{
		hour = hour - 12;
		amOrPM = " PM";			
	}

	//Really ugly way of adding "padding" to the number if it is less than 10
	std::ostringstream converter;

	if (hour <= 10 && min > 10 && second > 10) {
		converter << hour << ":" << min << ":" << second << amOrPM;
	}
	else if (min <= 10 && hour > 10 && second > 10) {
		converter << hour << ":" << "0" << min << ":" << second << amOrPM;
	}
	else if (second <= 10 && min > 10 && hour > 10) {
		converter << hour << ":" << min << ":" << "0" << second << amOrPM;
	}
	else if (hour <= 10 && min < 10 && second > 10) {
		converter << hour << ":" << "0" << min << ":" << second << amOrPM;
	}
	else if (hour >= 10 && min < 10 && second < 10) {
		converter << hour << ":" << "0" << min << ":" << "0" << second << amOrPM;
	}
	else if (hour <= 10 && min > 10 && second < 10) {
		converter << hour << ":" << min << ":" << "0" << second << amOrPM;
	}
	else if (hour >= 10 && min < 10 && second < 10) {
		converter << hour << ":" << "0" << min << ":" << "0" << second << amOrPM;
	}
	else {
		converter << hour << ":" << min << ":" << second << amOrPM;
	}

	std::string s(converter.str());
	//Renders the compiled time
	GLFont *timeText = new GLFont();
	timeText->Create("franklin_gothic.glf");
	timeText->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		timeText->RenderText(s.c_str(), brX - 98, tlY - 5, 0, 7);
	timeText->End();
	delete timeText;
}

void OGLStartBar::RenderStartMenu()
{
	menu_tlX = menu_topleft.GetX(), menu_tlY = menu_topleft.GetY();
	menu_blX = menu_bottomleft.GetX(), menu_blY = menu_bottomleft.GetY();
	menu_brX = menu_bottomright.GetX(), menu_brY = menu_bottomright.GetY();
	menu_trX = menu_topright.GetX(), menu_trY = menu_topright.GetY();

	//Renders the menu Panel 
	glBegin(GL_QUADS);
	glColor3f((startBarRed / 255.0f), (startBarGreen / 255.0f), (startBarBlue / 255.0f));
		glVertex2f(menu_tlX, menu_tlY);
		glVertex2f(menu_blX, menu_blY);
		glVertex2f(menu_brX, menu_brY);
		glVertex2f(menu_trX, menu_trY);
	glEnd();

	//Adds shadow Lines
	glLineWidth(3.0f);
	glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(menu_trX + 2.0f, menu_trY + 2.0f);
			glVertex2f(menu_tlX - 3.0f, menu_tlY + 2.0f);
			glVertex2f(menu_tlX - 1.0f, menu_tlY);
			glVertex2f(menu_blX - 1.0f, menu_blY);
	glEnd();

	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor3f(0.3f, 0.3f, 0.3f);
			glVertex2f(menu_trX + 1.0f, menu_trY + 1.0f);
			glVertex2f(menu_brX + 1.0f, menu_brY - 1.0f);
			glVertex2f(menu_brX + 1.0f, menu_brY - 1.0f);
			glVertex2f(menu_blX + 1, menu_brY - 1.0f);		
	glEnd();

	GLFont *programs = new GLFont();	//Renders the Programs text label and the arrow 
	programs->Create("another_font.glf");
	programs->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			programs->RenderText("Programs", menu_tlX + 50.0f, menu_tlY - 10.0f, 0, 8);
			programs->End();
	delete programs; 

	glBegin(GL_TRIANGLES);	//Programs arrow
		glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(menu_trX - 5.0f, (menu_trY - 20.0f));
			glVertex2f(menu_trX - 11.0f, (menu_trY - 25.0f));
			glVertex2f(menu_trX - 11.0f, (menu_trY - 15.0f));
	glEnd();

	GLFont *documents = new GLFont();	//Documents label 
	documents->Create("another_font.glf");
	documents->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			documents->RenderText("Documents", menu_tlX + 50.0f, menu_tlY - 50.0f, 0, 8);
			documents->End();
	delete documents;

	glLineWidth(2.0f);

	glBegin(GL_TRIANGLES);	//Documents arrow
		glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(menu_trX - 5.0f, (menu_trY - 60.0f));
			glVertex2f(menu_trX - 11.0f, (menu_trY - 65.0f));
			glVertex2f(menu_trX - 11.0f, (menu_trY - 55.0f));
	glEnd();

	GLFont *settings = new GLFont();
	settings->Create("another_font.glf");
	settings->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			settings->RenderText("Settings", menu_tlX + 50.0f, menu_tlY - 90.0f, 0, 8);
			settings->End();
	delete settings;

	glLineWidth(2.0f);

	glBegin(GL_TRIANGLES);		
		glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(menu_trX - 5.0f, (menu_trY - 100.0f));
			glVertex2f(menu_trX - 11.0f, (menu_trY - 105.0f));
			glVertex2f(menu_trX - 11.0f, (menu_trY - 95.0f));
	glEnd();

	RenderStartMenuTextures();
}

void OGLStartBar::RenderStartMenuTextures()
{
	/*Renders the textures in the start menu*/

	unsigned int texture[1];
	ImageReader *imageLoad = new ImageReader();
	imageLoad->LoadTGA("Icons\\ProgramsIcon.tga", &buffer, &sizeX, &sizeY, &bpp, &nChannels);
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glEnable(GL_BLEND);
	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f), glVertex2f(menu_tlX + 5.0f, menu_tlY - 5.0f);
			glTexCoord2f(1.0f, 0.0f), glVertex2f(menu_tlX + 5.0f, menu_tlY - 37.0f);
			glTexCoord2f(1.0f, 1.0f), glVertex2f(menu_tlX + 37.0f, menu_tlY - 37.0f);
			glTexCoord2f(0.0f, 1.0f), glVertex2f(menu_tlX + 37.0f, menu_tlY - 5.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//Clean up
	glDeleteTextures(1, texture);
	delete buffer, sizeX, sizeY, bpp, nChannels;

	imageLoad->LoadTGA("Icons\\DocumentsIcon.tga", &buffer, &sizeX, &sizeY, &bpp, &nChannels);
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

	glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glEnable(GL_BLEND);
	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f), glVertex2f(menu_tlX + 3.0f, menu_tlY - 42.0f);
			glTexCoord2f(1.0f, 0.0f), glVertex2f(menu_tlX + 3.0f, menu_tlY - 79.0f);
			glTexCoord2f(1.0f, 1.0f), glVertex2f(menu_tlX + 40.0f, menu_tlY - 79.0f);
			glTexCoord2f(0.0f, 1.0f), glVertex2f(menu_tlX + 40.0f, menu_tlY - 42.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//Clean up
	glDeleteTextures(1, texture);
	delete buffer, sizeX, sizeY, bpp, nChannels;

	imageLoad->LoadTGA("Icons\\SettingsIcon.tga", &buffer, &sizeX, &sizeY, &bpp, &nChannels);
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glEnable(GL_BLEND);
	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f), glVertex2f(menu_tlX + 3.0f, menu_tlY - 82.0f);
			glTexCoord2f(1.0f, 0.0f), glVertex2f(menu_tlX + 3.0f, menu_tlY - 119.0f);
			glTexCoord2f(1.0f, 1.0f), glVertex2f(menu_tlX + 40.0f, menu_tlY - 119.0f);
			glTexCoord2f(0.0f, 1.0f), glVertex2f(menu_tlX + 40.0f, menu_tlY - 82.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//Clean up
	glDeleteTextures(1, texture);
	delete buffer, sizeX, sizeY, bpp, nChannels;
	
	delete imageLoad; //clean up imageloader after its finished
}
void OGLStartBar::RenderStartMenuSlots()
{
	if (slotOneActive)
	{
		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, (175 / 255.0f));
				glVertex2f(menu_tlX, menu_tlY);
				glVertex2f(menu_tlX, menu_tlY - 40.0f);
				glVertex2f(menu_brX, menu_tlY - 40.0f);
				glVertex2f(menu_trX, menu_trY);
		glEnd();

		glBegin(GL_QUADS);
			glColor3f((startBarRed / 255.0f), (startBarGreen / 255.0f), (startBarBlue / 255.0f));
				glVertex2f(menu_trX, menu_trY);
				glVertex2f(menu_trX, menu_trY - 60.0f);
				glVertex2f(menu_trX + 150.0f, menu_trY - 60.0f);
				glVertex2f(menu_trX + 150.0f, menu_trY);
		glEnd();

		glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 1.0f);
				glVertex2f(menu_trX + 150.0f, menu_trY + 1.0f);
				glVertex2f(menu_trX - 2.0f, menu_trY + 1.0f);

				glVertex2f(menu_trX - 1.0f, menu_trY + 1.0f);
				glVertex2f(menu_trX - 1.0f, menu_trY - 62.0f);

			glColor3f(0.3f, 0.3f, 0.3f);
				glVertex2f(menu_trX + 150.0f, menu_trY + 1);
				glVertex2f(menu_trX + 150.0f, menu_trY - 62.0f);
				glVertex2f(menu_trX + 150.0f, menu_trY - 61.0f);
				glVertex2f(menu_trX - 1.0f, menu_trY - 61.0f);
		glEnd();

		//Re-renders the labels and arrows in white (when hovered over)
		GLFont *programs = new GLFont();
		programs->Create("another_font.glf");
		programs->Begin();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				programs->RenderText("Programs", menu_tlX + 50.0f, menu_tlY - 10.0f, 0, 8);
				programs->End();
		delete programs;

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);
				glVertex2f(menu_trX - 5.0f, (menu_trY - 20.0f));
				glVertex2f(menu_trX - 11.0f, (menu_trY - 25.0f));
				glVertex2f(menu_trX - 11.0f, (menu_trY - 15.0f));
		glEnd();

		if (slotOneDrawer1Active)
		{
			glBegin(GL_QUADS);
				glColor3f(0.0f, 0.0f, (175 / 255.0f));
					glVertex2f(menu_trX, menu_trY);
					glVertex2f(menu_trX, menu_trY - 30.0f);
					glVertex2f(menu_trX + 150.0f, menu_trY - 30.0f);
					glVertex2f(menu_trX + 150.0f, menu_trY);
			glEnd();
		}
		if (slotOneDrawer2Active)
		{
			glBegin(GL_QUADS);
				glColor3f(0.0f, 0.0f, (175 / 255.0f));
					glVertex2f(menu_trX, menu_trY- 30.0f);
					glVertex2f(menu_trX, menu_trY - 60.0f);
					glVertex2f(menu_trX + 150.0f, menu_trY - 60.0f);
					glVertex2f(menu_trX + 150.0f, menu_trY - 30.0f);
			glEnd();
		}
	}
	if (slotTwoActive)
	{
		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, (175 / 255.0f));
				glVertex2f(menu_tlX, menu_tlY - 40.0f);
				glVertex2f(menu_tlX, menu_tlY - 80.0f);
				glVertex2f(menu_brX, menu_tlY - 80.0f);
				glVertex2f(menu_trX, menu_trY - 40.0f);
		glEnd();

		GLFont *documents = new GLFont();
			documents->Create("another_font.glf");
			documents->Begin();
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					documents->RenderText("Documents", menu_tlX + 50.0f, menu_tlY - 50.0f, 0, 8);
					documents->End();
		delete documents;

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);
				glVertex2f(menu_trX - 5.0f, (menu_trY - 60.0f));
				glVertex2f(menu_trX - 11.0f, (menu_trY - 65.0f));
				glVertex2f(menu_trX - 11.0f, (menu_trY - 55.0f));
		glEnd();
	}
	if (slotThreeActive)
	{
		glBegin(GL_QUADS);
			glColor3f(0.0f, 0.0f, (175 / 255.0f));
				glVertex2f(menu_tlX, menu_tlY - 80.0f);
				glVertex2f(menu_tlX, menu_tlY - 120.0f);
				glVertex2f(menu_brX, menu_tlY - 120.0f);
				glVertex2f(menu_trX, menu_trY - 80.0f);
		glEnd();

		GLFont *settings = new GLFont();
			settings->Create("another_font.glf");
			settings->Begin();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			settings->RenderText("Settings", menu_tlX + 50.0f, menu_tlY - 90.0f, 0, 8);
			settings->End();
		delete settings;

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);
				glVertex2f(menu_trX - 5.0f, (menu_trY - 100.0f));
				glVertex2f(menu_trX - 11.0f, (menu_trY - 105.0f));
				glVertex2f(menu_trX - 11.0f, (menu_trY - 95.0f));
		glEnd();
	}

	RenderStartMenuTextures();
}

void OGLStartBar::RenderWindowTabs()
{
	////wt1_tlx, wt1_tly, wt1_blx, wt1_bly, wt1_brx, wt1_bry, wt1_trX, wt1_trY;
	//wt1_tlx = windowTab1_topLeft.GetX(), wt1_tly = windowTab1_topLeft.GetY();
	//wt1_blx = windowTab1_bottomLeft.GetX(), wt1_bly = windowTab1_bottomLeft.GetY();
	//wt1_brx = windowTab1_bottomRight.GetX(), wt1_bry = windowTab1_bottomRight.GetY();
	//wt1_trx = windowTab1_topRight.GetX(), wt1_try = windowTab1_topRight.GetY();

	//glBegin(GL_QUADS);
	////	glColor3f((startBarRed / 255.0f), (startBarGreen / 255.0f), (startBarBlue / 255.0f));
	//	glColor3f(0.0f, 1.0f, 1.0f);
	//		glVertex2f(wt1_tlx, wt1_tly);
	//		glVertex2f(wt1_blx, wt1_bly);
	//		glVertex2f(wt1_brx, wt1_bry);
	//		glVertex2f(wt1_trx, wt1_try);
	//glEnd();
	//
	//wt2_tlx = windowTab2_topLeft.GetX(), wt2_tly = windowTab2_topLeft.GetY();
	//wt2_blx = windowTab2_bottomLeft.GetX(), wt2_bly = windowTab2_bottomLeft.GetY();
	//wt2_brx = windowTab2_bottomRight.GetX(), wt2_bry = windowTab2_bottomRight.GetY();
	//wt2_trx = windowTab2_topRight.GetX(), wt2_try = windowTab2_topRight.GetY();

	//glBegin(GL_QUADS);
	////	glColor3f((startBarRed / 255.0f), (startBarGreen / 255.0f), (startBarBlue / 255.0f));
	//	glColor3f(0.0f, 1.0f, 1.0f);
	//		glVertex2f(wt2_tlx, wt2_tly);
	//		glVertex2f(wt2_blx, wt2_bly);
	//		glVertex2f(wt2_brx, wt2_bry);
	//		glVertex2f(wt2_trx, wt2_try);
	//glEnd();
}

void OGLStartBar::Render()
{
	RenderStartBar();
	RenderStartButton();
	Time();

	if (mouseOverTime) { 
		RenderTimeOver(); }	
	
	if (startButtonActive)
	{
		RenderStartMenu();
		RenderStartMenuSlots();
	}

	RenderWindowTabs();
}

void OGLStartBar::RenderTimeOver()
{
	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			glVertex2f(timeOverx - 225.0f, timeOvery + 35.0f);
			glVertex2f(timeOverx - 225.0f, timeOvery + 15.0f);
			glVertex2f(timeOverx + 50.0f, timeOvery + 15.0f);
			glVertex2f(timeOverx + 50.0f, timeOvery + 35.0f);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glVertex2f(timeOverx - 225.0f, timeOvery + 35.0f);
			glVertex2f(timeOverx - 225.0f, timeOvery + 15.0f);

			glVertex2f(timeOverx - 225.0f, timeOvery + 15.0f);
			glVertex2f(timeOverx + 50.0f, timeOvery + 15.0f);

			glVertex2f(timeOverx + 50.0f, timeOvery + 15.0f);
			glVertex2f(timeOverx + 50.0f, timeOvery + 35.0f);

			glVertex2f(timeOverx + 50.0f, timeOvery + 35.0f);
			glVertex2f(timeOverx - 225.0f, timeOvery + 35.0f);
	glEnd();

	std::ostringstream date;
	date << c_Day << ", " << dateNumber << " " << c_Month << " " << year;
	std::string t(date.str());

	GLFont *timeText1 = new GLFont();
	timeText1->Create("franklin_gothic.glf");
	timeText1->Begin();
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	timeText1->RenderText(t.c_str(), timeOverx - 200.0f, timeOvery + 35.0f, 0, 7);
	timeText1->End();
	//Clean up 
	delete timeText1;
}

void OGLStartBar::SetBarColour(float red, float green, float blue)
{
	startBarRed = red;
	startBarGreen = green;
	startBarBlue = blue;
}

bool OGLStartBar::MouseMove(int x, int y)
{
	if ((float)x > (brX - 100.0f) && (float)x < (brX - 3.0f) && (float)y < (brY + 24.0f) && (float)y > (brY + 3.0f))
	{
		mouseOverTime = true;
		timeOverx = x;
		timeOvery = y;
	}
	else
	{
		mouseOverTime = false;
	}

	if (startButtonActive)
	{
		if ((float)x > menu_tlX && (float)x < menu_trX && (float)y < menu_tlY && (float)y >(menu_tlY - 40.0f) || x > menu_trX && x < menu_trX + 150.0f && y < menu_trY && y > menu_trY - 60.0f)
		{
			slotOneActive = true;

			if (x > menu_trX && x < menu_trX + 150.0f && y < menu_trY && y > menu_trY - 30.0f)
			{
				slotOneDrawer1Active = true;
			}
			else
			{
				slotOneDrawer1Active = false; 
			}
			if (x > menu_trX && x < menu_trX + 150.0f && y < menu_trY - 30.0f && y > menu_trY - 60.0f)
			{
				slotOneDrawer2Active = true;
			}
			else
			{
				slotOneDrawer2Active = false;
			}
		}
		else
		{
			slotOneActive = false;
			slotOneDrawer1Active = false; 
		}
		

		if ((float)x > menu_tlX && (float)x < menu_trX && (float)y < menu_tlY - 40.0f && (float)y > menu_tlY - 80.0f)
		{
			slotTwoActive = true;
		}
		else
		{
			slotTwoActive = false;
		}

		if ((float)x > menu_tlX && (float)x < menu_trX && (float)y < menu_tlY - 80.0f && (float)y > menu_tlY - 120.0f)
		{
			slotThreeActive = true;
		}
		else
		{
			slotThreeActive = false;
		}
	}

	return true;
}

bool OGLStartBar::MouseLBUp(int x, int y)
{
	if ((float)x > sbtlX && (float)x < sbtrX && (float)y < sbtlY && (float)y > sbblY)
	{
		return true;
	}
	return true;
}

bool OGLStartBar::MouseLBDown(int x, int y)
{
	if ((float)x > sbtlX && (float)x < sbtrX && (float)y < sbtlY && (float)y > sbblY)
	{
		if (topShadow == 1.0f && bottomShadow == 0.3f)
		{
			topShadow = 0.3f;
			bottomShadow = 1.0f;

			startButtonActive = true; 

		}
		else
		{
			topShadow = 1.0f;
			bottomShadow = 0.3f;

			startButtonActive = false; 
		}
		return true;
	}
	else 
	{
		topShadow = 1.0f;
		bottomShadow = 0.3f;
		startButtonActive = false;
		return false;
	}
}

bool OGLStartBar::MouseRBDown(int x, int y)
{
	return true;
}
