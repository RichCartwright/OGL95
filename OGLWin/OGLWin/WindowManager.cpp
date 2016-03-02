#include "WindowManager.h"
#include "OGLStartBar.h"

WindowManager* WindowManager::s_wndmgr = NULL;

WindowManager::WindowManager()
{
	s_wndmgr = NULL;
}

WindowManager::~WindowManager()
{
	//Cleanup other stuff if necessary
	
	delete s_wndmgr;
}

void WindowManager::Create()
{
	if ( !s_wndmgr ) s_wndmgr = new WindowManager();
	{
	}
}

void WindowManager::Destroy()
{
	if ( s_wndmgr ) delete s_wndmgr;
}
