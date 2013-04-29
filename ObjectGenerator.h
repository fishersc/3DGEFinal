#pragma once
#ifndef OBJECT_GENERATOR_H
#define OBJECT_GENERATOR_H

#include <glm\glm.hpp>

/**
   Used to generate the data for various shapes.
   Currently can generate:
      - Cuboids
**/
class ObjectGenerator
{
private:
   struct Vector3 { float x, y, z; };

public:
   ObjectGenerator(void);
   ~ObjectGenerator(void);

   // Generates a white cuboid, each vertex has 11 components - 4 for position,
   // 4 for color, and 3 for normals.
   // Params
   //    width - the width of the cuboid
   //    height - the height of the cuboid
   //    depth - the depth of the cuboid
   static float* generateCuboid(float width, float height, float depth);

   // Generates a white wireframe cuboid, each vertex has 8 components - 4 for position
   // and 4 for color.
   // Params
   //    width - the width of the cuboid
   //    height - the height of the cuboid
   //    depth - the depth of the cuboid
   static float* generateLineCuboid(float width, float height, float depth);

   // Generates the positions, colors (white), and normals for the vertices
   // of a sphere.
   // The very first element is the number of vertices
   // Params
   //    radius - the radius of the sphere
   //    slices - the number of longitudinal elements
   //    stacks - the number of latitudinal elements
   static float* generateSphere(float radius, int slices=14, int stacks=8);

   static float* generateCylinder(float radius=1, float height=1, int slices=14, int stacks=8);

   // Generates a flat surface
   // The very first element is the number of values
   static float* generateFlatSurface(float width, float depth, int rows=1, int cols=1);

   // Generates the points for a right-handed axes system
   // The very first element is the number of values
   static float* generateRightHandedAxes(float length = 1);

private:
   static Vector3 computeNormal(const Vector3& A, const Vector3& B, const Vector3& C); 
   static Vector3 adjustNormal(const Vector3& A); 

};

#endif

