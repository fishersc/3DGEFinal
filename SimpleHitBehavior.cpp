#include "SimpleHitBehavior.h"
#include "AbstractGameObject.h"
#include <glm\glm.hpp>

SimpleHitBehavior::SimpleHitBehavior(void)
{
   currentState = DOING_NOTHING;
}


SimpleHitBehavior::~SimpleHitBehavior(void)
{
}

void SimpleHitBehavior::updateState()
{
   if(!object) return;

   if(object->objectsHit.size() > 0){
      currentState = MOVING;
   }
   else{
      currentState = DOING_NOTHING;
   }
}

void SimpleHitBehavior::animate(float elapsedMS)
{
   if(!object) return;

   if(currentState == MOVING){
      glm::vec3 pos = object->frame.getPosition();
      for(int i = 0; i < object->objectsHit.size(); i++){
         pos += (object->objectsHit[i]->direction * object->objectsHit[i]->speed * elapsedMS/1000.0f);
         object->frame.rotateY(1);
         object->frame.setPosition(pos);
      }
   }
}
