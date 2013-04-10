#include "AbstractGameWorld.h"
#include "AbstractGameObject.h"
#ifndef GAME_ENGINE_H
#include "GameEngine.h"
#endif

AbstractGameWorld::AbstractGameWorld(GameEngine* gameEngine)
{
   this->gameEngine = gameEngine;
}


AbstractGameWorld::~AbstractGameWorld(void)
{
   std::vector<AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      delete *io;
   }
}
