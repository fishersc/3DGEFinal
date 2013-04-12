#pragma once
#include "oglcompositegameobject.h"
#ifndef MY_COMPOSITE_OBJECT
#define MY_COMPOSITE_OBJECT
#endif
#include "Cuboid.h"
class Laser :
	public OGLCompositeGameObject
{
	 Cuboid* laser;
private:
   float angleY;
   float angleZ, speedZ;
public:
	Laser(const glm::vec3& pos);
	~Laser(void);
	void update();
   void animate(float dutationMS);
   void render();

   void setTransformMatrixUniform(GLuint unif);
   void setAmbientIntensityUniform(GLuint unif);
   void setSpecularUniform(GLuint unif);
   void setShininessUniform(GLuint unif);
   void setShader(GLuint shader);
};

