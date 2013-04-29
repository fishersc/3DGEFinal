#pragma once
#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <glm/glm.hpp>

class BoundingBox
{
public:
   bool use;
   glm::mat4 orientation;

private:
   float width, height, depth;

public:
   BoundingBox(float width=0, float height=0, float depth=0);
   ~BoundingBox(void);

   inline void set(float width, float height, float depth);

   inline float getWidth() const ;
   inline float getHeight() const;
   inline float getDepth() const;

   glm::vec3 getCenter() const;

   glm::vec3 getFrontNormal() const;
   glm::vec3 getUpNormal() const;
   glm::vec3 getRightNormal() const;

   bool overlapsWith(const BoundingBox& other);

private:
   float getProjection(const glm::vec3& vector, const glm::vec3& pAxis) const;
};

#endif

