#pragma once
#ifndef AXIS_H
#define AXIS_H

#include "oglgameobject.h"

class Axis : public OGLGameObject
{
public:
   Axis(float length = 1);
   virtual ~Axis(void);
};

#endif

