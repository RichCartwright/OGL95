#include "PhotoView.h"
#include <Windows.h>
#include <gl/GL.h>
#include "OGLWindowMaker.h"
#include "GLFont.h"
#include "freeglut.h"
#include "ImageReader.h"

PhotoView::PhotoView()
{
	photos[0] = "Photos\\photo1.tga";
}

PhotoView::~PhotoView()
{

}

void PhotoView::setXY(float tlX, float tlY, float trX, float trY, float blX, float blY, float brX, float brY)
{
	m_tlX = tlX, m_tlY = tlY, m_trX = trX, m_trY = trY;
	m_blX = blX, m_blY = blY, m_brX = brX, m_brY = brY;
	glScissor(m_blX, m_blY, (m_trX - m_tlX), (m_tlY, m_blY));
}

void PhotoView::setAlpha(float _alpha)
{
	alpha = _alpha;
}

void PhotoView::RenderViewArea()
{
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(m_tlX, m_tlY);
			glVertex2f(m_blX, m_blY);
			glVertex2f(m_brX, m_brY);
			glVertex2f(m_trX, m_trY);
	glEnd();
}

void PhotoView::Render()
{
	RenderViewArea();
	RenderIconsQuads();
}

void PhotoView::RenderIconsQuads()
{
	float tlX = m_tlX + 20.0f, tlY = m_tlY - 20.0f;

	glBegin(GL_QUADS);

	glEnable(GL_BLEND);
		glColor4f(1.0f, 0.0f, 1.0f, alpha);

		glTexCoord2f(0.0f, 0.0f), glVertex2f(tlX, tlY);
		glTexCoord2f(1.0f, 0.0f), glVertex2f(tlX, tlY - 60.0f);
		glTexCoord2f(1.0f, 1.0f), glVertex2f(tlX + 60.0f, tlY - 60.0f);
		glTexCoord2f(0.0f, 1.0f), glVertex2f(tlX + 60.0f, tlY);

	photo_tl[0].SetX(tlX), photo_tl[0].SetY(tlY), photo_bl[0].SetX(tlX), photo_bl[0].SetY(tlY - 60.0f);
	photo_br[0].SetX(tlX + 60.0f), photo_br[0].SetY(tlY - 60.0f), photo_tr[0].SetX(tlX + 60.0f), photo_tr[0].SetY(tlY);


	for (int i = 1; i < 20; i++)
	{
		tlX += 100.0f;

		//If the new quad location is going to go over the bounds
		//Reset the X to the left-hand size and drop it down 
		if (tlX + 60.0f > m_trX - 5.0f)
		{
			tlX = m_tlX + 20.0f;
			tlY -= 100.0f;
		}
		glEnable(GL_BLEND);
		glColor4f(1.0f, 0.0f, 1.0f, alpha);
		glVertex2f(tlX, tlY);
		glVertex2f(tlX, tlY - 60.0f);
		glVertex2f(tlX + 60.0f, tlY - 60.0f);
		glVertex2f(tlX + 60.0f, tlY);

		photo_tl[i].SetX(tlX), photo_tl[i].SetY(tlY), photo_bl[i].SetX(tlX), photo_bl[i].SetY(tlY - 60.0f);
		photo_br[i].SetX(tlX + 60.0f), photo_br[i].SetY(tlY - 60.0f), photo_tr[i].SetX(tlX + 60.0f), photo_tr[i].SetY(tlY);

		}
	glEnd();
}

bool PhotoView::MouseMove(int x, int y)
{
	return false;
}

bool PhotoView::MouseLBUp(int x, int y)
{
	return false;
}

bool PhotoView::MouseLBDown(int x, int y)
{
	return false;
}

bool PhotoView::MouseRBDown(int x, int y)
{
	return false;
}
