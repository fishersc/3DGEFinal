#include "BackForthBehavior.h"
#include "AbstractGameObject.h"

#include <iostream>

BackForthBehavior::BackForthBehavior(void)
{
   forthPoint.x = forthPoint.y = forthPoint.z;
   backPoint.x = backPoint.y = backPoint.z;
   currentState = MOVING_FORTH;
}


BackForthBehavior::~BackForthBehavior(void)
{
}

void BackForthBehavior::updateState()
{
   if(!object) return;

   glm::vec3 pos = object->frame.getPosition();
   float distance;

   switch(currentState){
   case MOVING_FORTH:
      distance = glm::length(forthPoint - pos);
      if(distance <= 0.09f){
         currentState = MOVING_BACK;
      }
      if(object->objectsHit.size() > 0){
         currentState = MOVING_BACK;
         pos += (-object->direction * 0.1f);
         object->frame.setPosition(pos);
      }
      break;
   case MOVING_BACK:
      distance = glm::length(backPoint - pos);
      if(distance <= 0.09f){
         currentState = MOVING_FORTH;
      }
      if(object->objectsHit.size() > 0){
         currentState = MOVING_FORTH;
         pos += (-object->direction * 0.1f);
         object->frame.setPosition(pos);
      }
      break;
   }
}

void BackForthBehavior::animate(float elapsedMS)
{
   if(!object) return;

   glm::vec3 pos = object->frame.getPosition();

   switch(currentState){
   case MOVING_FORTH:
      object->direction = glm::normalize(forthPoint - pos);
      break;
   case MOVING_BACK:
      object->direction = glm::normalize(backPoint - pos);
      break;
   }
   pos += (object->direction * object->speed * elapsedMS/1000.0f);
   object->frame.setPosition(pos);
}
