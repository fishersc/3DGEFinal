#pragma once
#ifndef OBJECT_DATA_H
#define OBJECT_DATA_H

#include <string>
#include <vector>

/**
   Encapsulates the data needed to render objects
**/
class ObjectData
{
public:
   enum DrawPrimitive { POINTS = 0, LINES = 1, TRIANGLES = 2 };
   enum StoredType { POSITION = 0, COLOR = 1, NORMAL = 2 };
   static const int STORED_TYPE_COUNT = 3;

   // Defaults
   static const int DEFAULT_COMPONENT_COUNT = 4;
   static const int DEFAULT_STARTING_OFFSET = 0;
   static const int DEFAULT_STRIDE = 0;

private:
   // Tracks the manual addition of vertices
   int index;

   // Tracks the manual addition of colors
   int colorIndex;

   // Tracks the manual addition of normals
   int normalIndex;

protected:
   // The number of elements
   int count;

   // Pointer to the data -- allocated on the heap
   float* data;

   // The number of components in the vectors
   // index 0 maps to position
   // index 1 maps to color
   int componentCount[STORED_TYPE_COUNT];

   // The starting offsets i.e. the number of bytes to the first item
   // index 0 maps to position
   // index 1 maps to color
   int startingOffset[STORED_TYPE_COUNT];

   // The stride - the number of bytes from the start of one item to the start of the next item.  
   // Zero stride means the items are next to each other.
   // index 0 maps to position
   // index 1 maps to color
   int stride[STORED_TYPE_COUNT];

   // The primitive of elements to draw.
   DrawPrimitive primitive;

public:
   ObjectData(void);
   ObjectData(const ObjectData& copy);
   const ObjectData& operator=(const ObjectData& rhs);
   ~ObjectData(void);

   // Returns the size in bytes
   inline int sizeInBytes() const { return count * sizeof(float); }

   // Returns the stored data
   inline float* getData() { return data; }

   // Sets the data from an incoming array - the array needs to be created
   // on the heap
   inline void setData(float* data) 
   {
      for(int i = 0; i < count; i++){
         this->data[i] = data[i]; 
      }
   }

   // Returns the number of elements
   inline int getCount() const { return count; }

   // Returns the number of vertices
   inline int getNumberOfVertices() const { return (count / (componentCount[POSITION]+componentCount[COLOR]+componentCount[NORMAL])); }

   // Returns the component count of a stored type
   int getComponentCount(StoredType type) const;

   // Returns the starting offset of a stored type
   int getStartingOffset(StoredType type) const;

   // Returns the stride of a stored type
   int getStride(StoredType type) const;

   // Returns the stored primitive
   inline int getPrimitive() const { return primitive; }

   // Reads the data from a file
   void readFromFile(std::string filename);

   // Sets the number of data elements
   void setCount(int count);

   // Sets positional components
   void setPositionComponents(int count, int offset, int stride);
   void setColorComponents(int count, int offset, int stride);
   void setNormalComponents(int count, int offset, int stride);

   void setPrimitive(int primitive);

   void addVertex(float x, float y, float z, float r, float g, float b); 
   void addColor(float r, float g, float b, float a=1);
   void addNormal(float x, float y, float z);

   // Adds random colors
   void addRandomColors(int vertexCount);
   // Set the object to a single color
   void setToOneColor(float r, float g, float b, float a=1);

   void consoleDump() const;

private:

   void copy(const ObjectData& rhs);
};

#endif

