#pragma once
#include "AbstractBehavior.h"
#include <glm\glm.hpp>
class LaserBehavior :
	public AbstractBehavior
{
public:
   bool canFire;
public:
	LaserBehavior(void);
	~LaserBehavior(void);
	 void animate(float elapsedMS);
	 bool fire();
};

