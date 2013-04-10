#pragma once
#ifndef REFERENCE_FRAME_H
#define REFERENCE_FRAME_H

#include <glm\glm.hpp>

#include "OGLUtil.h"

/**
   Represents the reference frame of a game object
**/
class ReferenceFrame
{
public:
   // The object's orientation and position
   glm::mat4 orientation;

public:
   // Constructor
   ReferenceFrame(void);

   // Destructor
   ~ReferenceFrame(void);

   // Sets the position 
   void setPosition(const glm::vec3& position);

   // Gets the position
   glm::vec3 getPosition() { return glm::vec3(orientation[3]); }

   inline void rotateX(float degrees) { orientation *= glm::mat4(OGLUtil::rotateX(degrees)); }

   inline void rotateY(float degrees) { orientation *= glm::mat4(OGLUtil::rotateY(degrees)); }

   inline void rotateZ(float degrees) { orientation *= glm::mat4(OGLUtil::rotateZ(degrees)); }

   inline void translate(float x, float y, float z) { orientation *= OGLUtil::translate(x, y, z); }

   void scale(const glm::vec3& scaleVec);

   void translate(const glm::vec3& offset);
};

#endif

