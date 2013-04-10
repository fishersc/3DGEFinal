#pragma once
#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm\glm.hpp>
#include <GL\glew.h>

class PointLight
{
public:
   glm::vec4 position;
   glm::vec4 intensity;

public:
   PointLight(void);
   ~PointLight(void);
};

#endif

