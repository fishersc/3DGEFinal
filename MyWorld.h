#pragma once
#ifndef MY_WORLD_H
#define MY_WORLD_H

#include <vector>
using namespace std;

#include "oglgameworld.h"
#include "PointLight.h"
#include "LineCuboid.h"

class MyWorld : public OGLGameWorld
{
protected:
   PointLight light;
   float lightSpeed;

   // So that we can see the bounding boxes
   vector<LineCuboid*> boxes;

public:
   MyWorld(OGLGameEngine* gameEngine);
   virtual ~MyWorld(void);
   void fireLaser();


   void doWorldEvent(int number, float durationMS);

   virtual void setupShaders();
   virtual void setupLights();
   virtual void updateCamera();
   virtual void updateViewport(float aspectRatio);
   virtual void animate(float durationMS);
   virtual void render();
   void checkForCollisions();
   int count;
   int rateCount;

   

protected:
   virtual void createGameObjects();

   void showBoundingBoxes();
};

#endif

