#pragma once
#ifndef LINE_CUBOID_H
#define LINE_CUBOID_H

#include "oglgameobject.h"

#include <glm\glm.hpp>

class LineCuboid : public OGLGameObject
{
protected:
   float width, height, depth;

public:
   LineCuboid(float width=1.0f, float height=1.0f, float depth=1.0f);
   LineCuboid(const LineCuboid& copy);
   virtual ~LineCuboid(void);

   inline float getWidth() const { return width; }
   inline float getHeight() const { return height; }
   inline float getDepth() const { return depth; }

   // Generates the cuboid.  The faces of the cuboid are wound counter-clockwise.
   void generate();
};

#endif

