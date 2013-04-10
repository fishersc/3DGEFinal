#include "PCInputSystem.h"


PCInputSystem::PCInputSystem(void)
{
   for(int i = 0; i < sizeof(keys); i++){
      keys[i] = false;
   }
   mouseX = mouseY = 0;
}


PCInputSystem::~PCInputSystem(void)
{
}
