#pragma once
#ifndef SIMPLE_HIT_BEHAVIOR_H
#define SIMPLE_HIT_BEHAVIOR_H

#include "abstractbehavior.h"

class SimpleHitBehavior : public AbstractBehavior
{
   enum SimpleHitState { DOING_NOTHING, MOVING };

protected:
   SimpleHitState currentState;

public:
   SimpleHitBehavior(void);
   virtual ~SimpleHitBehavior(void);

   void updateState();
   void animate(float elapsedMS);
};

#endif

