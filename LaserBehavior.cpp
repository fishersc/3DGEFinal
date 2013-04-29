#include "LaserBehavior.h"
#include "AbstractGameObject.h"
#include "ReferenceFrame.h"


LaserBehavior::LaserBehavior(void)
{	
   speed = 5;
}


LaserBehavior::~LaserBehavior(void)
{
}

void LaserBehavior::fire(const glm::vec3& position, const ReferenceFrame& frame)
{
	this->frame = frame;
}

void LaserBehavior::animate(float elapsedMS)
{
	if(!object) return;

   glm::vec3 pos = object->frame.getPosition();
   glm::vec3 dir;
   
   //switch(currentState) {

   //}
   pos += (1 * speed * elapsedMS/1000.0f);
   object->frame.setPosition(pos);
}
