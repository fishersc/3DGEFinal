#pragma once
#ifndef ABSTRACT_GAME_WORLD_H
#define ABSTRACT_GAME_WORLD_H

#include <vector>

class AbstractGameObject;
class GameEngine;

class AbstractGameWorld
{
public:
   std::vector<AbstractGameObject*> objects;

protected:
   GameEngine* gameEngine;

public:
   AbstractGameWorld(GameEngine* gameEngine);
   virtual ~AbstractGameWorld(void);

   virtual void initialize() = 0;
   virtual void update() = 0;
   virtual void animate(float durationMS) = 0;
   virtual void render() = 0;
   virtual void updateCamera() = 0;
   virtual void updateViewport(float aspectRatio) = 0;
};

#endif

