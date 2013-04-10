#include "GameEngine.h"
#include "AbstractCamera.h"

#ifndef ABSTRACT_GAME_WORLD_H
#include "AbstractGameWorld.h"
#endif

GameEngine::GameEngine(void)
{
	gameOver = false;
   windowWidth = windowHeight = 0;
   timer = NULL;
   gameLogicFrequency = DEFAULT_GAME_LOGIC_FREQUENCY;
   nextTime = 0;
   tickTime = 1000.0f/gameLogicFrequency;
   camera = NULL;
   gameWorld = NULL;
}

void GameEngine::startTiming()
{
   if(timer) timer->startTiming();
   tickTime = 1000.0f/gameLogicFrequency;
   updateTimingVariables();
}

bool GameEngine::isTimeToUpdateLogic() const
{
   return timer->getCurrentTimeInMilliseconds() >= nextTime;
}

void GameEngine::updateTimingVariables()
{
   if(timer) nextTime = timer->getCurrentTimeInMilliseconds() + tickTime;
}


GameEngine::~GameEngine(void)
{
   if(timer) delete timer;
   if(camera) delete camera;
   if(gameWorld) delete gameWorld;
}
