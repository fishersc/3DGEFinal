#pragma once
#ifndef ABSTRACT_BEHAVIOR_H
#define ABSTRACT_BEHAVIOR_H

class AbstractGameObject;

class AbstractBehavior
{
public:
   AbstractGameObject* object;

public:
   AbstractBehavior(void);
   virtual ~AbstractBehavior(void);

   virtual void updateState() = 0;
   virtual void animate(float elapsedMS) = 0;

};

#endif

