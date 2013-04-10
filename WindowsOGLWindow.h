#pragma once
#ifndef WINDOWS_OGL_WINDOW_H
#define WINDOWS_OGL_WINDOW_H

#include "WindowsWindow.h"
#include "OGLGameEngine.h"

/**
  Encapsulates a Windows based OpenGL window
*/
class WindowsOGLWindow : public WindowsWindow
{
protected:
   // Handle to the OpenGL rendering context
	HGLRC hrc;
   // Handle to the Windows device context
	HDC hdc;   // Device context
   // Stores the OpenGL version
	int glVersion[2];
   // References the game engine
	OGLGameEngine* gameEngine;
	// References itself 
	static WindowsOGLWindow* self;

public:
   // Constructor
   // Params:
   //   title - the window's title
   //   engine - pointer to the gme engine
	WindowsOGLWindow(const wstring& title, OGLGameEngine* engine);
   // Destructor
	~WindowsOGLWindow(void);
   // Processes the window's events
	virtual void processEvents();
   // Creates the window
	virtual bool create();
   // Returns the OpenGL program
	wstring getOpenGLVersionInformation() const;
   // Runs one frame of the game
	void runOneFrame();
   /**
      Purpose:
         Updates the size of the OpenGL viewport to the specified width and height
      Params:
         w - the new viewport's width
         h - the new viewport's height
      Returns:
         Nothing
      Pre:
         w > 0 and h > 0
         if Not Pre then the viewport's width and height are not changed.
      Post:
         The viewport's width and height are set to w and h respectively
   */
	void updateOGLViewportsize(int w, int h); 
   // Sets the game engine
	void setGameEngine(OGLGameEngine* gameEngine) { this->gameEngine = gameEngine; }
   // Initializes the windowed environment
	void initializeEnvironment();

protected:
   // The window procedure
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

#endif

