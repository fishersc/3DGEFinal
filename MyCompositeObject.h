#pragma once
#ifndef MY_COMPOSITE_OBJECT
#define MY_COMPOSITE_OBJECT

#include "oglcompositegameobject.h"
#include "Cuboid.h"

class MyCompositeObject :   public OGLCompositeGameObject
{
public:
   Cuboid* base;
   Cuboid* torso;
   Cuboid* turret;

private:
   float angleY;
   float angleZ, speedZ;

public:
   MyCompositeObject(const glm::vec3& pos);
   virtual ~MyCompositeObject(void);

   BoundingBox getOrientedBoundingBox();

   void update();
   void animate(float dutationMS);
   void render();
   void setTransformMatrixUniform(GLuint unif);
   void setAmbientIntensityUniform(GLuint unif);
   void setSpecularUniform(GLuint unif);
   void setShininessUniform(GLuint unif);
   void setShader(GLuint shader);
};

#endif

