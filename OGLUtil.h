#pragma once
#ifndef OGL_UTIL_H
#define OGL_UTIL_H

#include <GL\glew.h>
#include <glm\glm.hpp>

class OGLUtil
{
public:
	OGLUtil(void);
	virtual ~OGLUtil(void);

   static inline float degToRad(float degrees) { return degrees * 3.14159f / 180.0f; }
   static glm::mat3 rotateX(float degrees);
   static glm::mat3 rotateY(float degrees);
   static glm::mat3 rotateZ(float degrees);
   static glm::mat4 translate(float x, float y, float z);
};

#endif

