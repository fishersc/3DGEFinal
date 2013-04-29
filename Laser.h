#pragma once
#ifndef MY_COMPOSITE_OBJECT
#define MY_COMPOSITE_OBJECT
#endif
#include "Cuboid.h"
#include <string>

#include <glm\glm.hpp>
class Laser :
	public Cuboid
{
	 Cuboid* laser;
private:
   float angleY;
   float angleZ, speedZ;
public:
	string name;
	glm::vec3 startPos;
	float totalTime;
	Laser(float speed);
	~Laser(void);
   void animate(float dutationMS);
   void fire(const glm::vec3& position, const ReferenceFrame& frame);
};

