#include "Axis.h"
#include "ObjectGenerator.h"

Axis::Axis(float length)
{
   float* data = ObjectGenerator::generateRightHandedAxes(length);
   vertexData.setCount((int)data[0]);
   vertexData.setPositionComponents(4, 0, 32);
   vertexData.setColorComponents(4, 16, 32);
   vertexData.setNormalComponents(0, 0, 0);
   vertexData.setPrimitive(ObjectData::LINES);
   vertexData.setData(data+1);
   delete [] data;
}


Axis::~Axis(void)
{
}
