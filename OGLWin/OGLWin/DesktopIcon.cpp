#include "DesktopIcon.h"
#include "GLFont.h"
#include <Windows.h>
#include <gl/GL.h>
#include <sstream>
#include "freeglut.h"
#include "ImageReader.h"

DesktopIcon::DesktopIcon(float x, float y, iconType IconType)
{
	Icon_Type = IconType;
}

DesktopIcon::~DesktopIcon()
{
}

void DesktopIcon::setXY(float x, float y)
{
	m_topleft.SetX(x), m_topleft.SetY(y);
	m_topright.SetX(m_topleft.GetX() + 40.0f), m_topright.SetY(y);
	m_bottomleft.SetX(x), m_bottomleft.SetY(y - 40.0f);
	m_bottomright.SetX(m_topright.GetX()), m_bottomright.SetY(m_bottomleft.GetY());
}

void DesktopIcon::RenderIconQuad()
{
	tlX = m_topleft.GetX(), tlY = m_topleft.GetY();
	trX = m_topright.GetX(), trY = m_topright.GetY();
	blX = m_bottomleft.GetX(), blY = m_bottomleft.GetY();
	brX = m_bottomright.GetX(), brY = m_bottomright.GetY(); 
	//Renders the textures icon

	unsigned int texture[1];
	ImageReader *imageLoad = new ImageReader();

	unsigned char*			buffer;
	int						sizeX, sizeY, bpp, nChannels;

	//Uses the icon type enum to determine which one is being called 
	if (Icon_Type == ColourSelector)
	{
		imageLoad->LoadTGA("Icons\\ColourSelector.tga", &buffer, &sizeX, &sizeY, &bpp, &nChannels);
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glEnable(GL_BLEND);
		glBegin(GL_QUADS);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f), glVertex2f(tlX, tlY);
				glTexCoord2f(1.0f, 0.0f), glVertex2f(blX, blY);
				glTexCoord2f(1.0f, 1.0f), glVertex2f(brX, brY);
				glTexCoord2f(0.0f, 1.0f), glVertex2f(trX, trY);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//Clean up
		glDeleteTextures(1, texture);
		delete buffer, sizeX, sizeY, bpp, nChannels;

		GLFont *label = new GLFont();
		label->Create("another_font.glf");
		label->Begin();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				label->RenderText("Colour", tlX - 4.0f, blY, 0, 8);
				label->RenderText("Selector", tlX - 10.0f, blY - 14, 0, 8);
		label->End();
		delete label; //Clean up
	}
	if (Icon_Type == PhotoViewer)
	{
		imageLoad->LoadTGA("Icons\\PhotoViewerIcon.tga", &buffer, &sizeX, &sizeY, &bpp, &nChannels);
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glEnable(GL_BLEND);
		glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f), glVertex2f(tlX, tlY);
		glTexCoord2f(1.0f, 0.0f), glVertex2f(blX, blY);
		glTexCoord2f(1.0f, 1.0f), glVertex2f(brX, brY);
		glTexCoord2f(0.0f, 1.0f), glVertex2f(trX, trY);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//Clean up
		glDeleteTextures(1, texture);
		delete buffer, sizeX, sizeY, bpp, nChannels;

		GLFont *label = new GLFont();
		label->Create("another_font.glf");
		label->Begin();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		label->RenderText("Photo", tlX - 4.0f, blY, 0, 8);
		label->RenderText("Viewer", tlX - 7.0f, blY - 14, 0, 8);
		label->End();
		delete label; //Clean up 
	}
}

void DesktopIcon::Render()
{
	RenderIconQuad(); 
}

bool DesktopIcon::MouseMove(int x, int y)
{
	return false;
}

bool DesktopIcon::MouseLBUp(int x, int y)
{
	if (x > m_topleft.GetX() && x < m_topright.GetX() && y < m_topleft.GetY() && y > m_bottomleft.GetY())
	{
		return true; 
	}
	return false;
}

bool DesktopIcon::MouseLBDown(int x, int y)
{
	return false;
}

bool DesktopIcon::MouseRBDown(int x, int y)
{
	return false;
}
