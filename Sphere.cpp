#include "Sphere.h"
#include "ObjectGenerator.h"

Sphere::Sphere(const glm::vec3& position, float radius, int slices, int stacks)
{
   frame.setPosition(position);
   if(radius > 0) this->radius = radius;
   if(slices >= 5) this->slices = slices;
   if(stacks >= 5) this->stacks = stacks;

   generate();
}


Sphere::~Sphere(void)
{
}

void Sphere::generate()
{
   float* data = ObjectGenerator::generateSphere(radius, slices, stacks);
   // The first position in data has the number of vertices, each vertex has 11 components
   vertexData.setCount((int)data[0] * 11);
   vertexData.setPositionComponents(4, 0, 44);
   vertexData.setColorComponents(4, 16, 44);
   vertexData.setNormalComponents(3, 32, 44);
   vertexData.setPrimitive(ObjectData::TRIANGLES);
   
   vertexData.setData(data+1); // Skip the first index
   delete [] data;
}

