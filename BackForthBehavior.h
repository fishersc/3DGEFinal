#pragma once
#ifndef BACK_FORTH_BEHAVIOR_H
#define BACK_FORTH_BEHAVIOR_H

#include "AbstractBehavior.h"
#include <glm\glm.hpp>

class BackForthBehavior : public AbstractBehavior
{
public:
   enum BackForthState { MOVING_FORTH, MOVING_BACK };
   glm::vec3 forthPoint, backPoint;
   float speed;

protected:
   BackForthState currentState;

public:
   BackForthBehavior(void);
   virtual ~BackForthBehavior(void);

   void updateState();
   void animate(float elapsedMS);
};

#endif

