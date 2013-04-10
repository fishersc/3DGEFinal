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

public:
   // Constructor
   PCInputSystem(void);
   // Destructor
   ~PCInputSystem(void);
};

#endif

