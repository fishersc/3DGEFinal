#include "ShapeGenerator.h"

#include <cmath>
#include <iostream>
using namespace std;

ShapeGenerator::ShapeGenerator(void)
{
}


ShapeGenerator::~ShapeGenerator(void)
{
}

ShapeGenerator::Vector3 ShapeGenerator::computeNormal(const Vector3& A, const Vector3& B, const Vector3& C)
{
   glm::vec3 a(A.x, A.y, A.z);
   glm::vec3 b(B.x, B.y, B.z);
   glm::vec3 c(C.x, C.y, C.z);

   glm::vec3 AB = b - a;
   glm::vec3 AC = c - a;
   glm::vec3 r = glm::normalize(glm::cross(AB, AC));
   Vector3 v = {r.x, r.y, r.z};
   return v;
}

ShapeGenerator::Vector3 ShapeGenerator::adjustNormal(const Vector3& A)
{
   glm::vec3 a(A.x, A.y, A.z);
   glm::vec3 r = glm::normalize(a);
   Vector3 v = {r.x, r.y, r.z};
   return v;
}

float* ShapeGenerator::generateCuboid(float width, float height, float depth)
{
   float w2 = width/2, h2 = height/2, d2 = depth/2;

   Vector3 A = { -w2,  h2, d2 };
   Vector3 B = { -w2, -h2, d2 };
   Vector3 C = {  w2, -h2, d2 };
   Vector3 D = {  w2,  h2, d2 };

   Vector3 E = {  w2,  h2, -d2 };
   Vector3 F = {  w2, -h2, -d2 };
   Vector3 G = { -w2, -h2, -d2 };
   Vector3 H = { -w2,  h2, -d2 };

   Vector3 col = { 1, 1, 1 };

   Vector3 faces[6][6] = 
   {
      { A, B, C, C, D, A },
      { D, C, F, F, E, D },
      { E, F, G, G, H, E },
      { H, G, B, B, A, H },
      { H, A, D, D, E, H },
      { F, C, B, B, G, F }
   };

   Vector3 normals[6][6] = 
   {
      { computeNormal(A, B, C),  computeNormal(B, C, A), computeNormal(C, A, B), computeNormal(C, D, A),  computeNormal(D, A, C), computeNormal(A, C, D) },
      { computeNormal(D, C, F),  computeNormal(C, F, D), computeNormal(F, D, C), computeNormal(F, E, D),  computeNormal(E, D, F), computeNormal(D, F, E) },
      { computeNormal(E, F, G),  computeNormal(F, G, E), computeNormal(G, E, F), computeNormal(G, H, E),  computeNormal(H, E, G), computeNormal(E, G, H) },
      { computeNormal(H, G, B),  computeNormal(G, B, H), computeNormal(B, H, G), computeNormal(B, A, H),  computeNormal(A, H, B), computeNormal(H, B, A) },
      { computeNormal(H, A, D),  computeNormal(A, D, H), computeNormal(D, H, A), computeNormal(D, E, H),  computeNormal(E, H, D), computeNormal(H, D, E) },
      { computeNormal(F, C, B),  computeNormal(C, B, F), computeNormal(B, F, C), computeNormal(B, G, F),  computeNormal(G, F, B), computeNormal(F, B, G) }
   };

   // There are 6 faces with 2 triangles each.  Each triangle has 3 vertices with 11 components
   // 6 x 2 x 3 x 11 = 396 floats
   float* data = new float[396];

   int i = 0;
   for(int face = 0; face < 6; face++){
      for(int vertex = 0; vertex < 6; vertex++){
         data[i++] = faces[face][vertex].x;
         data[i++] = faces[face][vertex].y;
         data[i++] = faces[face][vertex].z;
         data[i++] = 1;

         data[i++] = col.x;
         data[i++] = col.y;
         data[i++] = col.z;
         data[i++] = 1;

         data[i++] = normals[face][vertex].x;
         data[i++] = normals[face][vertex].y;
         data[i++] = normals[face][vertex].z;
      }
   }
   return data;
}

float* ShapeGenerator::generateSphere(float radius, int slices, int stacks)
{
#define DEG2RAD(x) ((x) * 3.14159f / 180.0f)
#define SIND(x) (sinf(DEG2RAD(x)))
#define COSD(x) (cosf(DEG2RAD(x)))

   float rho = radius, phi = 0, theta = 0;
   float stepY = 180.0f / stacks;
   float stepX = 360.0f / slices;
   int middleStackCount = stacks - 2;
   float vertices = 0;

   // The top and bottom of the sphere has (slices x 3) vertices
   vertices += (2 * slices * 3);

   // The middle of the sphere has (stacks - 2) x slices x 6 vertices
   vertices += middleStackCount * slices * 6;

   // Each vertex has 11 components
   int numberOfFloats = (int)(vertices * 11) + 1; // Add one to store the number of vertices

   float* data = new float[numberOfFloats];
   data[0] = vertices;

   int i = 1;
   float x = 0, y = radius, z = 0;

   Vector3 A, B, C, D, N;
   phi = stepY;
   // Generate the top 
   float sinPhi = 0, cosPhi = 0, cosTheta = 0, sinTheta = 0;
   for(theta = 0; theta < 360.0f; theta += stepX){
      sinPhi = SIND(phi);
      cosPhi = COSD(phi);
      cosTheta = COSD(theta);
      sinTheta = SIND(theta);

      A.x = (rho * sinPhi * sinTheta);
      A.y = (rho * cosPhi);
      A.z = (rho * sinPhi * cosTheta);

      cosTheta = COSD(theta + stepX);
      sinTheta = SIND(theta + stepX);

      B.x = (rho * sinPhi * sinTheta);
      B.y = A.y;
      B.z = (rho * sinPhi * cosTheta);

      C.x = 0;
      C.y = radius;
      C.z = 0;

      // First vertex
      data[i++] = A.x;
      data[i++] = A.y;
      data[i++] = A.z;
      data[i++] = 1;
      // Color
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1; 

      //N = computeNormal(A, B, C);
      N = adjustNormal(A);
      data[i++] = N.x;
      data[i++] = N.y;
      data[i++] = N.z;

      // second vertex
      data[i++] = B.x;
      data[i++] = B.y;
      data[i++] = B.z;
      data[i++] = 1;
      // Color
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1; 

      N = adjustNormal(B);
      data[i++] = N.x;
      data[i++] = N.y;
      data[i++] = N.z;

      // Third vertex is the north pole
      data[i++] = C.x;
      data[i++] = C.y;
      data[i++] = C.z;
      data[i++] = 1;
      // Color
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1; 

      N = adjustNormal(C);
      data[i++] = N.x;
      data[i++] = N.y;
      data[i++] = N.z;
   }

   float phiUp = phi;
   float phiDown = phi + stepY;
   
   // Generate the middle
   for(int s = 0; s < middleStackCount; s++){
      // We need to generate 4 vertices for each facet
      for(theta = 0; theta < 360.0f; theta += stepX){
         // D   C
         // +---+
         // |\  |
         // | \ |
         // |  \|
         // +---+
         // A   B

         sinPhi = SIND(phiDown);
         cosPhi = COSD(phiDown);
         cosTheta = COSD(theta);
         sinTheta = SIND(theta);

         x = (rho * sinPhi * sinTheta);
         y = (rho * cosPhi);
         z = (rho * sinPhi * cosTheta);

         A.x = x;
         A.y = y;
         A.z = z;

         cosTheta = COSD(theta + stepX);
         sinTheta = SIND(theta + stepX);

         x = (rho * sinPhi * sinTheta);
         z = (rho * sinPhi * cosTheta);

         B.x = x;
         B.y = y;
         B.z = z;

         sinPhi = SIND(phiUp);
         cosPhi = COSD(phiUp);

         x = (rho * sinPhi * sinTheta);
         y = (rho * cosPhi);
         z = (rho * sinPhi * cosTheta);

         C.x = x;
         C.y = y;
         C.z = z;

         cosTheta = COSD(theta);
         sinTheta = SIND(theta);

         x = (rho * sinPhi * sinTheta);
         z = (rho * sinPhi * cosTheta);

         D.x = x;
         D.y = y;
         D.z = z;

         // A->B->D
         // -------

         // A
         data[i++] = A.x;
         data[i++] = A.y;
         data[i++] = A.z;
         data[i++] = 1;
         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1; 

         N = adjustNormal(A);
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         // B
         data[i++] = B.x;
         data[i++] = B.y;
         data[i++] = B.z;
         data[i++] = 1;
         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1; 

         N = adjustNormal(B);
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         // D
         data[i++] = D.x;
         data[i++] = D.y;
         data[i++] = D.z;
         data[i++] = 1;
         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1; 

         N = adjustNormal(D);
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         // B->C->D
         // -------

         // B
         data[i++] = B.x;
         data[i++] = B.y;
         data[i++] = B.z;
         data[i++] = 1;
         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1; 

         N = adjustNormal(B);
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         // C
         data[i++] = C.x;
         data[i++] = C.y;
         data[i++] = C.z;
         data[i++] = 1;
         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1; 

         N = adjustNormal(C);
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         // D
         data[i++] = D.x;
         data[i++] = D.y;
         data[i++] = D.z;
         data[i++] = 1;
         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1; 

         N = adjustNormal(D);
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;
      } // end for theta
      phiUp = phiDown;
      phiDown += stepY;
   } // end for each middle stack

   phi = phiUp;
   // Generate the bottom 
   for(theta = 0; theta < 360.0f; theta += stepX){
      sinPhi = SIND(phi);
      cosPhi = COSD(phi);
      cosTheta = COSD(theta);
      sinTheta = SIND(theta);

      A.x = (rho * sinPhi * sinTheta);
      A.y = (rho * cosPhi);
      A.z = (rho * sinPhi * cosTheta);

      B.x = 0;
      B.y = -radius;
      B.z = 0;

      cosTheta = COSD(theta + stepX);
      sinTheta = SIND(theta + stepX);

      C.x = (rho * sinPhi * sinTheta);
      C.y = A.y;
      C.z = (rho * sinPhi * cosTheta);

      // First vertex
      data[i++] = A.x;
      data[i++] = A.y;
      data[i++] = A.z;
      data[i++] = 1;
      // Color
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1; 

      N = adjustNormal(A);
      data[i++] = N.x;
      data[i++] = N.y;
      data[i++] = N.z;

      // Second vertex is the south pole
      data[i++] = B.x;
      data[i++] = B.y;
      data[i++] = B.z;
      data[i++] = 1;
      // Color
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1; 

      N = adjustNormal(B);
      data[i++] = N.x;
      data[i++] = N.y;
      data[i++] = N.z;

      // third vertex
      data[i++] = C.x;
      data[i++] = C.y;
      data[i++] = C.z;
      data[i++] = 1;
      // Color
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1;
      data[i++] = 1; 

      N = adjustNormal(C);
      data[i++] = N.x;
      data[i++] = N.y;
      data[i++] = N.z;
   }
   return data;
}

float* ShapeGenerator::generateFlatSurface(float width, float depth, int rows, int cols)
{
   if(width <= 0) width = 1;
   if(depth <= 0) depth = 1;
   if(rows <= 0) rows = 1;
   if(cols <= 0) cols = 1;

   // /----  width  ----\
   // 
   // +---+---+     +---+   \
   // |\  |\  |     |\  |   |
   // | \ | \ | ... | \ |   |
   // |  \|  \|     |  \|   
   // +---+---+     +---+   d
   //     .     .     .     e
   //     .      .    .     p
   //     .       .   .     t
   // +---+---+     +---+   h
   // |\  |\  |     |\  |   
   // | \ | \ | ... | \ |   |
   // |  \|  \|     |  \|   |
   // +---+---+     +---+   /

   float cellWidth = width/cols;
   float cellDepth = depth/rows;

   float w2 = width/2;
   float d2 = depth/2;

   // Each cell has 2 triangles, each triangle has 3 vertices
   int numberOfVertices = rows * cols * 2 * 3;

   // Each vertex has 11 elements
   int numberOfFloats = (numberOfVertices * 11);

   // Add 1 to store the extra data
   float* data = new float[numberOfFloats+1];
   data[0] = (float)numberOfFloats;

   // D       C
   // +-------+
   // |\      |
   // | \     |
   // |  \    |
   // |   \   |
   // |    \  |
   // |     \ |
   // |      \|
   // +-------+
   // A       B
   Vector3 A, B, C, D, N;
   float sx = 0, sz = -d2;
   int i = 1;
   for(int row = 0; row < rows; row++){
      sx = -w2;
      for(int col = 0; col < cols; col++){
         A.x = sx;
         A.y = 0;
         A.z = sz + cellDepth;

         B.x = sx + cellWidth;
         B.y = 0;
         B.z = A.z;

         C.x = B.x;
         C.y = 0;
         C.z = sz;

         D.x = A.x;
         D.y = 0;
         D.z = C.z;

         // Since the surface is flat the normal should be the same for 
         // all vertices of the cell
         N = computeNormal(A, B, D);

         // A->B->D
         // -------

         data[i++] = A.x;
         data[i++] = A.y;
         data[i++] = A.z;
         data[i++] = 1;

         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;

         // Normal
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         data[i++] = B.x;
         data[i++] = B.y;
         data[i++] = B.z;
         data[i++] = 1;

         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;

         // Normal
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         data[i++] = D.x;
         data[i++] = D.y;
         data[i++] = D.z;
         data[i++] = 1;

         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;

         // Normal
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         // B->C->D
         // -------

         data[i++] = B.x;
         data[i++] = B.y;
         data[i++] = B.z;
         data[i++] = 1;

         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;

         // Normal
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         data[i++] = C.x;
         data[i++] = C.y;
         data[i++] = C.z;
         data[i++] = 1;

         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;

         // Normal
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         data[i++] = D.x;
         data[i++] = D.y;
         data[i++] = D.z;
         data[i++] = 1;

         // Color
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;
         data[i++] = 1;

         // Normal
         data[i++] = N.x;
         data[i++] = N.y;
         data[i++] = N.z;

         sx += cellWidth;
      }
      sz += cellDepth;
   }
   return data;
}
