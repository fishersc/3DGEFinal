#pragma once
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "PCInputSystem.h"
#include "AbstractTimer.h"

#include <string>
using std::wstring;

class AbstractCamera;
class AbstractGameWorld;

/**
  Encapsulates the essential elements of the game engine.
*/
class GameEngine
{
public:
   static const int DEFAULT_GAME_LOGIC_FREQUENCY = 100;

protected:
   // Used to indicate when th game is over
	bool gameOver;

   // Used to specify the number of times per second to run the game logic
   int gameLogicFrequency;

   // Used to store the next time to update
   float nextTime;

   // Used to store the tick time
   float tickTime;

public:
   // The game engine has an input system
   PCInputSystem inputSystem;

   // The game engine references a timer.  This timer should be created on the heap.
   AbstractTimer* timer;

   // The game engine references a camera.  This camera should be created on the heap
   AbstractCamera* camera;

   // Reference to the game world
   AbstractGameWorld* gameWorld;

   // The window's width and height
   int windowWidth, windowHeight;

public:
   // Constructor
	GameEngine(void);

   // Destructor
	virtual ~GameEngine(void);

   // Returns true if the game is over
	bool isGameOver() const { return gameOver; }

   // Sets the game over flag to true
	void setGameOver()      { gameOver = true; }

   // Should be used to initialize elements of the game engine
	virtual void initialize() {}

   // Should be used to realize the game logic
	virtual void gameLogic(float tickTimeMS) {}

   // Should be used to present the game
   virtual void gamePresentation() {}

   // Should be used to set the aspect ratio of the game
   // Params:
   //   aspectRatio - the aspect ration of the viewing area
	virtual void setAspectRatio(float aspectRatio) {}

   // Starts the timer
   virtual void startTiming();

   // Returns true if its time to update the logic
   virtual bool isTimeToUpdateLogic() const;

   // Updates lastTime
   virtual void updateTimingVariables();

   // Getter
   inline float getTickTime() const { return tickTime; }

   // Should be used to update the camera's state
   virtual void cameraUpdate() {}

   // Should be used to update the player's state
   virtual void playerUpdate(float tickTimeMS) {}
  
};

#endif

