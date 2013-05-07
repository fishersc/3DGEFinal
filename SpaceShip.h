#pragma once
#include "oglcompositegameobject.h"
#include "Pyramid.h"
#include "Cuboid.h"
#include "Sphere.h"
#include "Cylinder.h"

class SpaceShip :
	public OGLCompositeGameObject
{
	public:
   Cuboid* body;
   Cuboid* engineConnector1;
   Cuboid* engineConnector2;
   Cylinder* engine1;
   Cylinder* engine2;
   Cuboid* spoilerside1;
	Cuboid* spoilerside2;
	Cuboid* spoilertop;
   Sphere* cockpit2;
   Pyramid* cockpit1;
   Pyramid* thruster1;
   Pyramid* thruster2;
   glm::vec3 gun;

   float speed;
   float strafe;
   float MaxSpeed;
   float LimitStrafe;
   float strafePOS;
private:
   float angleY;
   float angleZ, speedZ;
public:
	SpaceShip(const glm::vec3& pos);
	~SpaceShip(void);
	void update();
   void animate(float dutationMS);
   void render();

   virtual void setTransformMatrixUniform(GLuint unif);
   void setAmbientIntensityUniform(GLuint unif);
   void setSpecularUniform(GLuint unif);
   void setShininessUniform(GLuint unif);
   void setShader(GLuint shader);
};

