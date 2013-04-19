#pragma once
#include "oglcompositegameobject.h"
#include "Pyramid.h"
#include "Cuboid.h"
class SpaceShip :
	public OGLCompositeGameObject
{
	public:
   Cuboid* body;
   Cuboid* engineConnector1;
   Cuboid* engineConnector2;
   Cuboid* engine1;
   Cuboid* engine2;
   Cuboid* cockpit2;
   Pyramid* cockpit1;
   Pyramid* thruster1;
   Pyramid* thruster2;
private:
   float angleY;
   float angleZ, speedZ;
public:
	SpaceShip(void);
	~SpaceShip(void);
	void update();
   void animate(float dutationMS);
   void render();

   virtual void setTransformMatrixUniform(GLuint unif);
};

