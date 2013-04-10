#pragma once
#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

class GameEngine;
class AbstractWindow;

/**
  Encapsulates the game's engine and the UI
*/
class GameApplication
{
private:
   /**
     This object "owns" the game engine
   */
	GameEngine* gameEngine;
   /**
     This object "owns" the UI window
   */
	AbstractWindow* window;

public:
   /**
     The constructor
   */
	GameApplication(GameEngine* engine, AbstractWindow* window);
   /**
     The destructor
   */
	~GameApplication(void);
   /**
     Starts the application
   */
	void run();
};

#endif

