#include "RandomWaypointBehavior.h"
#include "AbstractGameObject.h"

RandomWaypointBehavior::RandomWaypointBehavior(float minX, float maxX, float minZ, float maxZ, float y)
{
   this->minX = minX;
   this->maxX = maxX;
   this->minZ = minZ;
   this->maxZ = maxZ;
   this->y = y;
   generateWaypoint();
}


RandomWaypointBehavior::~RandomWaypointBehavior(void)
{
}

void RandomWaypointBehavior::generateWaypoint()
{
   wayPoint.y = y;
   float newX = (rand() % (int)(maxX - minX)) + minX;
   float newZ = (rand() % (int)(maxZ - minZ)) + minZ;
   if(wayPoint.x  == minX)
   {
	   wayPoint.x = maxX;
   }
   else
   {
		wayPoint.x = minX;
   }
	wayPoint.z = newZ;
   
}

void RandomWaypointBehavior::updateState()
{
   if(!object) return;

   glm::vec3 pos = object->frame.getPosition();
   float distance = glm::length(wayPoint.x - pos.x);
   if(distance <= 0.09f){
      generateWaypoint();
   }

   if(object->objectsHit.size() > 0){
      wayPoint.x = -wayPoint.x;
      wayPoint.z = -wayPoint.z;
   }
}

void RandomWaypointBehavior::animate(float elapsedMS)
{
   if(!object) return;

   glm::vec3 pos = object->frame.getPosition();
   object->direction = glm::normalize(wayPoint - pos);
   pos += (object->direction * (object->speed+100) * elapsedMS/1000.0f);
   //object->frame.rotateY(2);
   object->frame.setPosition(pos);
   
}
