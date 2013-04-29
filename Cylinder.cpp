#include "Cylinder.h"
#include "ObjectGenerator.h"
#include "BoundingBox.h"

Cylinder::Cylinder(const glm::vec3& position, float radius, float height, int slices, int stacks)
{
   frame.setPosition(position);
   this->slices = 5;
   this->stacks = 1;
   if(radius > 0) this->radius = radius;
   if(height > 0) this->height = height;
   if(slices >= 5) this->slices = slices;
   if(stacks >= 1) this->stacks = stacks;

   generate();
}


Cylinder::~Cylinder(void)
{
}

void Cylinder::generate()
{
   float* data = ObjectGenerator::generateCylinder(radius, height, slices, stacks);
   vertexData.setCount((int)data[0]);
   vertexData.setPositionComponents(4, 0, 44);
   vertexData.setColorComponents(4, 16, 44);
   vertexData.setNormalComponents(3, 32, 44);
   vertexData.setPrimitive(ObjectData::TRIANGLES);
   vertexData.setData(data+1); // Skip the first index
   delete [] data;
}

BoundingBox Cylinder::getOrientedBoundingBox()
{
   float width = radius * 2;
   return OGLGameObject::getOrientedBoundingBox(width, height, width);
}
