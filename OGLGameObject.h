#pragma once
#ifndef OGL_GAME_OBJECT_H
#define OGL_GAME_OBJECT_H

#include "abstractgameobject.h"

#include <GL\glew.h>

class BoundingBox;

class OGLGameObject :  public AbstractGameObject
{
protected:
   GLuint vboID;

public:
   GLuint transformMatrixUnif;
   GLuint ambientIntensityUnif;
   GLuint normTransformMatrixUnif;
   GLuint specularUnif;
   GLuint shininessUnif;

protected:
   GLuint shader;

public:
   OGLGameObject(void);
   OGLGameObject(const OGLGameObject& copy);
   virtual ~OGLGameObject(void);

   virtual void render();

   virtual void setTransformMatrixUniform(GLuint unif);
   virtual void setNormalTransformMatrixUniform(GLuint unif);
   virtual void setAmbientIntensityUniform(GLuint unif);
   virtual void setSpecularUniform(GLuint unif);
   virtual void setShininessUniform(GLuint unif);
   virtual void setShader(GLuint shader) { this->shader = shader; }
   virtual BoundingBox getOrientedBoundingBox(float width, float height, float depth);
   virtual BoundingBox getOrientedBoundingBox();

   void createFromFile(std::string filename);

   void update();
   void animate(float durationMS);
   void render(const ReferenceFrame& frame);

   void generateVBO();

protected:
   GLuint createHandle(GLenum target, const void* bufferData, GLsizei bufferSize);

   
};

#endif
