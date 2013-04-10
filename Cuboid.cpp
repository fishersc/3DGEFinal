#include "Cuboid.h"
#include "ShapeGenerator.h"
#include <cstdlib>
#include <time.h> 
#include <iostream>

Cuboid::Cuboid(const glm::vec3& position, float width, float height, float depth) : OGLGameObject()
{
   frame.setPosition(position);
   if(width > 0) this->width = width;
   if(height > 0) this->height = height;
   if(depth > 0) this->depth = depth;

   generate();
}


Cuboid::~Cuboid(void)
{
}

void Cuboid::generate()
{
   // 12 triangles, 3 vertices each, 11 values (position, color, and normal) = 288
   vertexData.setCount(396);
   vertexData.setPositionComponents(4, 0, 44);
   vertexData.setColorComponents(4, 16, 44);
   vertexData.setNormalComponents(3, 32, 44);
   vertexData.setPrimitive(ObjectData::TRIANGLES);
   float* data = ShapeGenerator::generateCuboid(width, height, depth);
   vertexData.setData(data);
   delete [] data;
}

void Cuboid::update()
{
}

void Cuboid::animate(float durationMS)
{
}