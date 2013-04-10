#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "oglgameobject.h"
#include <glm\glm.hpp>


class Sphere : public OGLGameObject
{
private:
   int slices, stacks;
   float radius;

public:
   Sphere(const glm::vec3& position=glm::vec3(), float radius=1.0f, int slices=14, int stacks=8);
   virtual ~Sphere(void);

   // Generates the cuboid.  The faces of the cuboid are wound counter-clockwise.
   void generate();
};

#endif

