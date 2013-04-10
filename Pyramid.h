#pragma once
#ifndef PYRAMID_H
#define PYRAMID_H

#include "oglgameobject.h"

class Pyramid :  public OGLGameObject
{
private:
   float angleZ;

public:
   Pyramid(void);
   virtual ~Pyramid(void);

   void update() {}

   void animate(float durationMS);
};

#endif

