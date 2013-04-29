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
   wayPoint.x = (rand() % (int)(maxX - minX)) + minX;
   wayPoint.z = (rand() % (int)(maxZ - minZ)) + minZ;
}

void RandomWaypointBehavior::updateState()
{
   if(!object) return;

   glm::vec3 pos = object->frame.getPosition();
   float distance = glm::length(wayPoint - pos);
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
   pos += (object->direction * object->speed * elapsedMS/1000.0f);
   object->frame.rotateY(2);
   object->frame.setPosition(pos);
   
}
