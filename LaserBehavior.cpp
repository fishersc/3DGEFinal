#include "LaserBehavior.h"
#include "AbstractGameObject.h"


LaserBehavior::LaserBehavior(void)
{	
   speed = 5;
}


LaserBehavior::~LaserBehavior(void)
{
}

void LaserBehavior::animate(float elapsedMS)
{
	if(!object) return;

   glm::vec3 pos = object->frame.getPosition();

   pos += (1 * speed * elapsedMS/1000.0f);
   object->frame.setPosition(pos);
}
