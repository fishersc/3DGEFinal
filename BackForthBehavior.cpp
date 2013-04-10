#include "BackForthBehavior.h"
#include "AbstractGameObject.h"

#include <iostream>

BackForthBehavior::BackForthBehavior(void)
{
   forthPoint.x = forthPoint.y = forthPoint.z;
   backPoint.x = backPoint.y = backPoint.z;
   currentState = MOVING_FORTH;
   speed = 5;
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
      break;
   case MOVING_BACK:
      distance = glm::length(backPoint - pos);
      if(distance <= 0.09f){
         currentState = MOVING_FORTH;
      }
      break;
   }
}

void BackForthBehavior::animate(float elapsedMS)
{
   if(!object) return;

   glm::vec3 pos = object->frame.getPosition();
   glm::vec3 dir;

   switch(currentState){
   case MOVING_FORTH:
      dir = glm::normalize(forthPoint - pos);
      break;
   case MOVING_BACK:
      dir = glm::normalize(backPoint - pos);
      break;
   }
   pos += (dir * speed * elapsedMS/1000.0f);
   object->frame.setPosition(pos);
}
