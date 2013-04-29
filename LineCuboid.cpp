#include "LineCuboid.h"
#include "ObjectGenerator.h"

LineCuboid::LineCuboid(float width, float height, float depth)
{
   if(width > 0) this->width = width;
   if(height > 0) this->height = height;
   if(depth > 0) this->depth = depth;

   generate();
}

LineCuboid::LineCuboid(const LineCuboid& cpy) : OGLGameObject(cpy)
{
   width = cpy.width;
   height = cpy.height;
   depth = cpy.height;
}


LineCuboid::~LineCuboid(void)
{
}

void LineCuboid::generate()
{
   float* data = ObjectGenerator::generateLineCuboid(width, height, depth);
   vertexData.setCount((int)data[0]);
   vertexData.setPositionComponents(4, 0, 32);
   vertexData.setColorComponents(4, 16, 32);
   vertexData.setNormalComponents(0, 0, 0);
   vertexData.setPrimitive(ObjectData::LINES);
   vertexData.setData(data+1);
   delete [] data;
}
