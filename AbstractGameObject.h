#pragma once
#ifndef ABSTRACT_GAME_OBJECT_H
#define ABSTRACT_GAME_OBJECT_H

#include "ObjectData.h"
#include "ReferenceFrame.h"
#include "Material.h"

#include <string>
#include <vector>
using namespace std;

#include <glm\glm.hpp>

class AbstractBehavior;
class BoundingBox;

class AbstractGameObject
{
public:
   ObjectData vertexData;

   AbstractBehavior* behavior;

   Material material;

   ReferenceFrame frame;

   // The object's local position
   glm::vec3 localPosition;

   glm::vec3 direction;

   float speed;

   vector<AbstractGameObject*> objectsHit;

   bool useBoundingBox;

public:
   AbstractGameObject(void);
   AbstractGameObject(const AbstractGameObject& copy);
   virtual ~AbstractGameObject(void);

   virtual void update() = 0;
   virtual void animate(float durationMS) = 0;
   virtual void render() = 0;

   virtual void createFromFile(std::string filename) = 0;
   virtual BoundingBox getOrientedBoundingBox(float width, float height, float depth) = 0;
   virtual BoundingBox getOrientedBoundingBox() = 0;
};

#endif

