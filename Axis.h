#pragma once
#ifndef AXIS_H
#define AXIS_H

#include "oglgameobject.h"

class Axis : public OGLGameObject
{
public:
   Axis(void);
   virtual ~Axis(void);

   void update() {}
   void animate(float durationMS) {} 
};

#endif

