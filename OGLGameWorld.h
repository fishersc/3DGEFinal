#pragma once
#ifndef OGL_GAME_WORLD_H
#define OGL_GAME_WORLD_H

#include "AbstractGameWorld.h"
#include "PointLight.h"
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

   PointLight light;

   OGLShaderManager shaderMan;

   float lightSpeed;

   float zNear; 

	float zFar;

public:
   OGLGameWorld(OGLGameEngine* gameEngine);
   virtual ~OGLGameWorld(void);

   virtual void initialize();
   virtual void update();
   virtual void animate(float durationMS);
   virtual void render();
   virtual void updateCamera();
   virtual void updateViewport(float aspectRatio);
};

#endif

