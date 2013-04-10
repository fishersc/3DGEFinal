#include "GameApplication.h"
#include "WindowsConsoleLogger.h"
#include "WindowsOGLWindow.h"
#include "OGLGameEngine.h"

#ifndef NULL
#define NULL 0
#endif

GameApplication::GameApplication(GameEngine* gameEngine, AbstractWindow* window)
{
	this->gameEngine = NULL;
	this->window = NULL;
	if(gameEngine != NULL) this->gameEngine = gameEngine;
	if(window != NULL) this->window = window;

}

GameApplication::~GameApplication(void)
{
	if(gameEngine != NULL) delete gameEngine;
	if(window != NULL) delete window;
}

void GameApplication::run()
{
	if(this->window == NULL){
		WCLog::error(L"GameApplication::run()", L"The window was not initialized.");
		return;
	}
	if(this->gameEngine == NULL){
		WCLog::error(L"GameApplication::run()", L"The engine was not created.");
		return;
	}

	WindowsOGLWindow* window = (WindowsOGLWindow*)this->window;
	if(window->create()){
		WCLog::info(L"OpenGL Version", window->getOpenGLVersionInformation());
		window->initializeEnvironment();
		window->show();
		window->processEvents();
	}
	else{
		WCLog::error(L"GameApplication::run()", L"There was an error creating the window.");
	}
}
