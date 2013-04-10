#pragma once
#ifndef CUBOID_H
#define CUBOID_H

#include "oglgameobject.h"
#include <glm\glm.hpp>

/**
   Represents a cuboid object.  It generates its vertices in local space.
**/
class Cuboid : public OGLGameObject
{
protected:
   float width, height, depth;

public:
   // Constructor
   // Parameters:
   //    position - the center of the cuboid in world coordinates
   //    width - the width of the cuboid, defaults to 1, must be > than 0
   //    height - the height of the cuboid, defaults to 1, must be > than 0
   //    depth - the depth of the cuboid, defaults to 1, must be > than 0
   Cuboid(const glm::vec3& position, float width=1.0f, float height=1.0f, float depth=1.0f);

   // Destructor
   virtual ~Cuboid(void);

   void update();
   void animate(float durationMS);

   // Generates the cuboid.  The faces of the cuboid are wound counter-clockwise.
   void generate();

};

#endif

