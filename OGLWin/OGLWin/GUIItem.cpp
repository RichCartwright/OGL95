#include "GUIItem.h"

GUIItem::GUIItem()
{
	m_renderable = NULL;
}

GUIItem::~GUIItem()
{
	//TODO: Free up resource on delete
	//Q: Can you delete m_renderable if the renderable is shared by other GUI items?
}

bool GUIItem::MouseMove(int x, int y)
{
	return true;
}

bool GUIItem::MouseLBDown(int x, int y)
{
	return true;
}

bool GUIItem::MouseLBUp(int x, int y)
{
	return true;
}
