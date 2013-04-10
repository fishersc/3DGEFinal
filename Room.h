#pragma once
#ifndef ROOM_H
#define ROOM_H

#include "oglgameobject.h"

class Room : public OGLGameObject
{
public:
   Room(void);
   virtual ~Room(void);

   void update();
   void animate(float durationMS);
};

#endif

