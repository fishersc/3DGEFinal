#pragma once
#ifndef FLAT_SURFACE_H
#define FLAT_SURFACE_H

#include "oglgameobject.h"

class FlatSurface : public OGLGameObject
{
private:
   float width, depth;
   int rows, cols;

public:
   FlatSurface(float width=1, float depth=1, int rows=1, int cols=1);
   virtual ~FlatSurface(void);

   void update() {}
   void animate(float durationMS) {}

   // Generates the cuboid.  The faces of the cuboid are wound counter-clockwise.
   void generate();
};

#endif

