#include <Windows.h>
#include "PCInputSystem.h"


PCInputSystem::PCInputSystem(void)
{
   for(int i = 0; i < sizeof(keys); i++){
      keys[i] = false;
   }
   maxMouseX = maxMouseY = oldMouseX = oldMouseY = mouseX = mouseY = 0;
   mouseMoved = false;
   leftMouseButton = false;
   rightMouseButton = false;
   moveDirectionX = moveDirectionY = 0;
   blocked = false;
}


PCInputSystem::~PCInputSystem(void)
{
}

void PCInputSystem::moveMouse(int newMouseX, int newMouseY)
{
   if(blocked) return;
   mouseY = newMouseY;
   mouseX = newMouseX;
   if(newMouseX >= maxMouseX-10){
      mouseX = 1;
      blocked = true;
      SetCursorPos(mouseX, mouseY);
      blocked = false;
   }
   else if(newMouseX <= 0){
      mouseX = maxMouseX - 11;
      blocked = true;
      SetCursorPos(mouseX, mouseY);
      blocked = false;
   }
}
