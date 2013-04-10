#pragma once
#ifndef OGL_COMPOSITE_GAME_OBJECT_H
#define OGL_COMPOSITE_GAME_OBJECT_H

#include "oglgameobject.h"
#include "ReferenceFrameStack.h"

/**
   Represents a hierarchical game object
**/
class OGLCompositeGameObject :   public OGLGameObject
{
public:
   // A reference frame stack is used to manage the hierarchy
   ReferenceFrameStack frameStack;

public:
   OGLCompositeGameObject(void);
   virtual ~OGLCompositeGameObject(void);
};

#endif

