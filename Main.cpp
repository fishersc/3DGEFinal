#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glutilD.lib")

#include <Windows.h>
#include <time.h> 
#include "WindowsOGLWindow.h"
#include "OGLGameEngine.h"
#include "WindowsConsoleLogger.h"
#include "GameApplication.h"
 
/*
   The main entry point.
   Params:
   - hInstance     : handle to the current instance of the application (Not used)     
   - hPrevInstance : handle to the previous instance of the application, will always be NULL (Legacy, Not used)
   - lpCmdLine     : the command line of the application, excluding the program name (Not used)
   - nCmdShow      : controls how the window is to be shown (Not used)
   Returns:
   - an integer reporting the exit state of the application
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	WCLog::redirectIOToConsole(); 
   srand((unsigned int)time(NULL)); // Random seed

	GameEngine* gameEngine = new OGLGameEngine();
	GameApplication app(gameEngine, new WindowsOGLWindow(L"World with Oriented Bounding Boxes (OBB)", (OGLGameEngine*)gameEngine));
	
	app.run();

	return 0;
}


