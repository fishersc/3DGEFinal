#include "FlatSurface.h"
#include "ShapeGenerator.h"

FlatSurface::FlatSurface(float width, float depth, int rows, int cols)
{
   if(width <= 0) width = 1;
   if(depth <= 0) depth = 1;
   if(rows <= 0) rows = 1;
   if(cols <= 0) cols = 1;

   this->width = width;
   this->depth = depth;
   this->rows = rows;
   this->cols = cols;

   generate();
}


FlatSurface::~FlatSurface(void)
{
}

void FlatSurface::generate()
{
   float* data = ShapeGenerator::generateFlatSurface(width, depth, rows, cols);
   // The first position in data has the number of elements
   vertexData.setCount((int)data[0]);
   vertexData.setPositionComponents(4, 0, 44);
   vertexData.setColorComponents(4, 16, 44);
   vertexData.setNormalComponents(3, 32, 44);
   vertexData.setPrimitive(ObjectData::TRIANGLES);
   
   vertexData.setData(data+1); // Skip the first index
   delete [] data;
}

