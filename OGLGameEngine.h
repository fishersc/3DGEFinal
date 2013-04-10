#pragma once
#ifndef OGL_GAME_ENGINE_H
#define OGL_GAME_ENGINE_H

#include "GameEngine.h"
#include <GL\glew.h>

class OGLSphericalCamera;
class OGLReverseSphericalCamera;
class OGLGameWorld;
/**
   An OpenGL based game engine that inherits from the game engine
*/
class OGLGameEngine : public GameEngine
{
protected:
   // Used to manage the object to be rendered
	//OGLResource object;
   OGLGameWorld* gameWorld;

public:
   // Used so that we don't have to be type-casting everytime.  See the constructor
   OGLSphericalCamera* theCamera;
   OGLReverseSphericalCamera* camera2;

public:
   // Constructor
	OGLGameEngine(void);

   // Destructor
	virtual ~OGLGameEngine(void);

   // Initializes the OGL game engine
	void initialize();

   // The game logic
	void gameLogic(float tickTimeMS);

   // The game presentation
   void gamePresentation();

   // Sets the aspect ratio
   // Params:
   //    aspectRatio - the aspect ratio of the viewing area
   //                  aspectRatio > 0
	void setAspectRatio(float aspectRatio);

   // Updates the camera
   virtual void cameraUpdate();

   // Updates the player's state
   virtual void playerUpdate(float tickTimeMS);
   
};

#endif

