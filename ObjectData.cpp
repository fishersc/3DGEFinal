#include "ObjectData.h"
#include <iostream>
#include <fstream>

#ifndef NULL
#define NULL 0
#endif

ObjectData::ObjectData(void)
{
   index = 0;
   colorIndex = 0;
   normalIndex = 0;
   data = NULL;
   count = 0;
   componentCount[POSITION] = DEFAULT_COMPONENT_COUNT;
   componentCount[COLOR] = DEFAULT_COMPONENT_COUNT;
   startingOffset[POSITION] = DEFAULT_STARTING_OFFSET;
   startingOffset[COLOR] = DEFAULT_STARTING_OFFSET;
   stride[POSITION] = DEFAULT_STRIDE;
   stride[COLOR] = DEFAULT_STRIDE;
   primitive = TRIANGLES;
}


ObjectData::~ObjectData(void)
{
   if(data) delete [] data;
}

int ObjectData::getComponentCount(StoredType type) const
{
   int count = 0;
   if(type >= 0 && type < STORED_TYPE_COUNT){
      count = componentCount[type];
   }
   return count;
}

int ObjectData::getStartingOffset(StoredType type) const
{
   int offset = 0;
   if(type >= 0 && type < STORED_TYPE_COUNT){
      offset = startingOffset[type];
   }
   return offset;
}

int ObjectData::getStride(StoredType type) const
{
   int localStride = 0;
   if(type >= 0 && type < STORED_TYPE_COUNT){
      localStride = stride[type];
   }
   return localStride;
}

void ObjectData::readFromFile(std::string filename)
{
   std::string value;
	std::ifstream fin(filename.c_str());
	if(!fin.is_open()){
      std::cerr << "Cannot open file " << filename << std::endl;
      return;
   }

   // The file's content as a collection of floats
	std::vector<int> headers;

   // Read the header data.  There are 8 things to read: <count>,<position component count>,<position offset>,
   // <position stride>,<color component count>,<color offset>,<color stride>,<primitive>
   const int HEADER_COUNT = 8;
   int i = 0;
	while(i < HEADER_COUNT){
      if(fin.good()){
			getline(fin, value, ',');
			headers.push_back(atoi(value.c_str()));
      }
      else{
         std::cerr << "Error reading file " << filename << std::endl;
         break;
      }
      i++;
	} // EndWhile i < HEADER_COUNT

   if(headers.size() != HEADER_COUNT){
      std::cerr << "Expected 8 csv: <count>,<position component count>" 
         << ",<position offset>,<position stride>,<color component count>" 
         << ",<color offset>,<color stride>,<primitive>," << std::endl;
      fin.close();
      return;
   }

   count = headers[0];
   componentCount[POSITION] = headers[1];
   startingOffset[POSITION] = headers[2];
   stride[POSITION] = headers[3];
   componentCount[COLOR] = headers[4];
   startingOffset[COLOR] = headers[5];
   stride[COLOR] = headers[6];
   primitive = (DrawPrimitive)headers[7];

	std::vector<float> values;
   
   // Read the object data proper
   i = 0;
   while(fin.good()){
      getline(fin, value, ',');
		values.push_back((float)atof(value.c_str()));
   }
   fin.close();

   if(values.size() != count){
      std::cerr << "The number of data values do not match the header count." << std::endl;
      return;
   }

   data = new float[count];
	for(i = 0; i < count; i++){
		data[i] = values[i];
	}
}

void ObjectData::setCount(int count)
{
   if(count > 0){
      if(data) delete [] data;
      this->count = count;
      data = new float[this->count];
   }
}

void ObjectData::setPositionComponents(int count, int offset, int stride)
{
   this->componentCount[POSITION] = count;
   this->startingOffset[POSITION] = offset;
   this->stride[POSITION] = stride;
}

void ObjectData::setColorComponents(int count, int offset, int stride)
{
   this->componentCount[COLOR] = count;
   this->startingOffset[COLOR] = offset;
   this->stride[COLOR] = stride;
}

void ObjectData::setNormalComponents(int count, int offset, int stride)
{
   this->componentCount[NORMAL] = count;
   this->startingOffset[NORMAL] = offset;
   this->stride[NORMAL] = stride;
}

void ObjectData::setPrimitive(int primitive)
{
   if(primitive >= POINTS && primitive <= TRIANGLES){
      this->primitive = (DrawPrimitive)primitive;
   }
}

void ObjectData::addVertex(float x, float y, float z, float r, float g, float b)
{
   int colorOffset = 0;
   if(stride[POSITION] == 0){
      // This means all the components are next to each other
      colorOffset = index + (componentCount[POSITION] * getNumberOfVertices());
   }
   else{
      // Positions and colors are interleaved
      colorOffset = index + componentCount[POSITION];
   }

   data[index++] = x;
   data[index++] = y;
   data[index++] = z;
   if(componentCount[POSITION] == 4) data[index++] = 1.0f;

   data[colorOffset++] = r;
   data[colorOffset++] = g;
   data[colorOffset++] = b;
   if(componentCount[COLOR] == 4) data[colorOffset++] = 1.0f;

   if(stride[POSITION] != 0){
      index = colorOffset;
   }
}

void ObjectData::addColor(float r, float g, float b, float a)
{
   if(stride[COLOR] == 0){
      // This means all the color components are next to each other
      if(colorIndex == 0){
         colorIndex = componentCount[POSITION] * getNumberOfVertices();
      }
   }
   else{
      // Positions, colors, and normals are interleaved
      if(colorIndex == 0){
         colorIndex = startingOffset[COLOR] / sizeof(float);
      }
      else{
         colorIndex += (stride[COLOR] / sizeof(float)) - componentCount[COLOR];
      }
   }

   data[colorIndex++] = r;
   data[colorIndex++] = g;
   data[colorIndex++] = b;
   if(componentCount[COLOR] == 4){
      data[colorIndex++] = a;
   }
}

void ObjectData::addNormal(float x, float y, float z)
{
   if(stride[NORMAL] == 0){
      // This means all the normal components are next to each other
      if(normalIndex == 0){
         normalIndex = (componentCount[POSITION] + componentCount[COLOR]) * getNumberOfVertices();
      }
   }
   else{
      // Positions, colors, and normals are interleaved
      if(normalIndex == 0){
         normalIndex = startingOffset[NORMAL] / sizeof(float);
      }
      else{
         normalIndex += (stride[NORMAL] / sizeof(float)) - componentCount[NORMAL];
      }
   }
   data[normalIndex++] = x;
   data[normalIndex++] = y;
   data[normalIndex++] = z;
}

void ObjectData::addRandomColors(int vertexCount)
{
   colorIndex = 0;
   if(vertexCount < 1) vertexCount = 1;
   float r = 0, g = 0, b = 0;
   for(int i = 0; i < getNumberOfVertices()/vertexCount; i++){
      r = (rand() % 256) / 255.0f;
      g = (rand() % 256) / 255.0f;
      b = (rand() % 256) / 255.0f;
      for(int j = 0; j < vertexCount; j++){
         addColor(r, g, b);
      }
   }
}

void ObjectData::setToOneColor(float r, float g, float b, float a)
{
   colorIndex = 0;
   for(int i = 0; i < getNumberOfVertices(); i++){
      addColor(r, g, b, a);
   }
}

void ObjectData::consoleDump() const
{
   std::cout << "Count : " << count << std::endl << 
      "Components (position) " << componentCount[POSITION] << std::endl <<
      "Components (color) " << componentCount[COLOR] << std::endl <<
      "Components (normal) " << componentCount[NORMAL] << std::endl <<
      "Starting offset (position) " << startingOffset[POSITION] << std::endl <<
      "Starting offset (color) " << startingOffset[COLOR] << std::endl <<
      "Starting offset (normal) " << startingOffset[NORMAL] << std::endl <<
      "Stride (position) " << stride[POSITION] << std::endl <<
      "Stride (color) " << stride[COLOR] << std::endl <<
      "Stride (normal) " << stride[NORMAL] << std::endl <<
      "Primitive " << primitive << std::endl <<
      "Vertex Count " << getNumberOfVertices() << 
      "Size in bytes " << sizeInBytes() << std::endl;

   int c = 0;
   for(int i = 0; i < count; i++){
      if(c == 0 || c == 4 || c == 8){
         std::cout << std::endl;
      }
		std::cout << data[i] << ", ";
      if(++c == 11) c = 0;
	}
   std::cout << std::endl;
}