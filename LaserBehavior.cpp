#include "LaserBehavior.h"
#include "AbstractGameObject.h"
#include "ReferenceFrame.h"


LaserBehavior::LaserBehavior(void)
{	
	canFire = true;
}


LaserBehavior::~LaserBehavior(void)
{
}

bool LaserBehavior::fire()
{
	return canFire;
}

void LaserBehavior::animate(float elapsedMS)
{
	
}
