#pragma once
#ifndef OGL_GAME_WORLD_H
#define OGL_GAME_WORLD_H

#include "AbstractGameWorld.h"
#include "OGLShaderManager.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

// Requires the Unofficial OpenGL SDK http://glsdk.sourceforge.net/docs/html/index.html

class OGLGameEngine;

class OGLGameWorld : public AbstractGameWorld
{
protected:
   GLuint vaoID;

   glm::vec4 lightDirection;

   OGLShaderManager shaderMan;

   float zNear; 

	float zFar;

public:
   OGLGameWorld(OGLGameEngine* gameEngine);
   virtual ~OGLGameWorld(void);

   virtual void initialize();
   virtual void update();
   virtual void animate(float durationMS);
   virtual void render();

   virtual void updateViewport(float aspectRatio) {}
   virtual void updateCamera() {}
   virtual void setupShaders() {}
   virtual void setupLights() {}

protected:
   virtual void createGameObjects() = 0;

   virtual void checkForCollisions();
};

#endif

