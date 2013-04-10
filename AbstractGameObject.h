#pragma once
#ifndef ABSTRACT_GAME_OBJECT_H
#define ABSTRACT_GAME_OBJECT_H

#include "ObjectData.h"
#include "ReferenceFrame.h"
#include "Material.h"

#include <string>

class AbstractBehavior;

class AbstractGameObject
{
public:
   ObjectData vertexData;

   AbstractBehavior* behavior;

   Material material;

   ReferenceFrame frame;

public:
   AbstractGameObject(void);
   virtual ~AbstractGameObject(void);

   virtual void update() = 0;
   virtual void animate(float durationMS) = 0;
   virtual void render() = 0;

   virtual void createFromFile(std::string filename) = 0;
};

#endif

