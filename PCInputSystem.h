#pragma once
#ifndef PC_INPUT_SYSTEM_H
#define PC_INPUT_SYSTEM_H

/**
  Encpasulates a IBM-PC based input system
*/
class PCInputSystem
{
public:
   // Assumes the number of keys
   const static int NUM_KEYS = 256;
   // Set to true or false depending whether the key is pressed or not
   bool keys[NUM_KEYS];

   int mouseX, mouseY;

   
   bool leftMouseButton;
   bool rightMouseButton;

private:
   int oldMouseX, oldMouseY;
   bool mouseMoved;

   int moveDirectionX;
   int moveDirectionY;

   int maxMouseX, maxMouseY;

   bool blocked;

public:
   // Constructor
   PCInputSystem(void);
   // Destructor
   ~PCInputSystem(void);

   inline void setMaxMouse(int maxMouseX, int maxMouseY)
   {
      if(maxMouseX > 0) this->maxMouseX = maxMouseX;
      if(maxMouseY > 0) this->maxMouseY = maxMouseY;
   }

   void moveMouse(int newMouseX, int newMouseY);

   void blockMouseUpdate(bool blocked) { this->blocked = blocked; }

   inline bool getMouseMoved() const { return mouseMoved; }
   inline int getMoveDirectionX() const { return moveDirectionX; }
   inline int getMoveDirectionY() const { return moveDirectionY; }
   inline bool isMouseBlocked() const { return blocked; }

   inline float getMouseXRatio() const { return mouseX / (float)maxMouseX; }
   inline float getMouseYRatio() const { return mouseY / (float)maxMouseY; }
};

#endif

