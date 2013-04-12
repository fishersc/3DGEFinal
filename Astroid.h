#pragma once
#include "oglcompositegameobject.h"
#ifndef MY_COMPOSITE_OBJECT
#define MY_COMPOSITE_OBJECT
#endif
#include "Cuboid.h"

class Astroid :
	public OGLCompositeGameObject
{
	public:
   Cuboid* base;
   Cuboid* torso;
   Cuboid* turret;
     Cuboid* ast;
	   Cuboid* roid;
private:
   float angleY;
   float angleZ, speedZ;
public:
	Astroid(const glm::vec3& pos);
	virtual ~Astroid(void);
	void update();
   void animate(float dutationMS);
   void render();

   void setTransformMatrixUniform(GLuint unif);
   void setAmbientIntensityUniform(GLuint unif);
   void setSpecularUniform(GLuint unif);
   void setShininessUniform(GLuint unif);
   void setShader(GLuint shader);
};

