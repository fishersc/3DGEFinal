#pragma once
#include "AbstractBehavior.h"
#include <glm\glm.hpp>
class LaserBehavior :
	public AbstractBehavior
{
public:
   float speed;
public:
	LaserBehavior(void);
	~LaserBehavior(void);
	 void animate(float elapsedMS);
	 void fire(const glm::vec3& position, const ReferenceFrame& frame);
};

