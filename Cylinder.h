#pragma once
#ifndef CYLINDER_H
#define CYLINDER_H

#include "OglGameObject.h"

class Cylinder : public OGLGameObject
{
private:
   int slices, stacks;
   float radius, height;

public:
   Cylinder(const glm::vec3& position=glm::vec3(), float radius=1.0f, float height=1.0f, int slices=14, int stacks=8);
   virtual ~Cylinder(void);

   virtual BoundingBox getOrientedBoundingBox();

   void generate();
};

#endif

