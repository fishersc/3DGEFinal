#include "Windows.h"
#include "OGLGameEngine.h"
#include "OGLSphericalCamera.h"
#include "OGLReverseSphericalCamera.h"
#include "OGLGameWorld.h"
#include "MyWorld.h"
#include "SpaceShip.h"

#include <iostream>

OGLGameEngine::OGLGameEngine(void)
{
   gameWorld = new MyWorld(this);
   camera = new OGLSphericalCamera();
   camera2 = new OGLReverseSphericalCamera();
   theCamera = (OGLReverseSphericalCamera*)camera2;
   theCamera->position.x = 0;
   theCamera->position.y = 5;
   theCamera->position.z = 5;
}

OGLGameEngine::~OGLGameEngine(void)
{
   if(gameWorld) delete gameWorld;
   if(camera2) delete camera2;
}

void OGLGameEngine::initialize()
{
   theCamera->cameraPosSpherical.phi = -90.0f;  
   theCamera->cameraPosSpherical.theta = -20.0f;  
   theCamera->cameraPosSpherical.rho = -300.0f;  

   theCamera->cameraTarget.x = 0;
   theCamera->cameraTarget.y = 0;
   theCamera->cameraTarget.z = 0;

   gameWorld->initialize();
}

void OGLGameEngine::setAspectRatio(float aspectRatio)
{
   gameWorld->updateViewport(aspectRatio);
}

void OGLGameEngine::gameLogic(float tickTimeMS)
{
   gameWorld->update();
   gameWorld->animate(tickTimeMS);
}

void OGLGameEngine::gamePresentation()
{
   gameWorld->render();
}

void OGLGameEngine::playerUpdate(float tickTimeMS)
{
   if(inputSystem.keys['1']){ 
      gameWorld->doWorldEvent(1, tickTimeMS);
      inputSystem.keys['1'] = false;
   }else if(inputSystem.keys['2']){
      gameWorld->doWorldEvent(2, tickTimeMS);
      inputSystem.keys['2'] = false;
   }else if(inputSystem.keys['3']){
      gameWorld->doWorldEvent(3, tickTimeMS);
      inputSystem.keys['3'] = false;
   }else if(inputSystem.keys[VK_UP]){
      gameWorld->doWorldEvent(100, tickTimeMS);
      inputSystem.keys[VK_UP] = false;
   }else if(inputSystem.keys[VK_DOWN]){
      gameWorld->doWorldEvent(101, tickTimeMS);
      inputSystem.keys[VK_UP] = false;
   }else if(inputSystem.keys[VK_RIGHT]){
      gameWorld->doWorldEvent(102, tickTimeMS);
      inputSystem.keys[VK_RIGHT] = false;
   }else if(inputSystem.keys[VK_LEFT]){
      gameWorld->doWorldEvent(103, tickTimeMS);
      inputSystem.keys[VK_LEFT] = false;
   }
	else if(inputSystem.keys[VK_SPACE])
   {
	   gameWorld->doWorldEvent(300, tickTimeMS);
	   inputSystem.keys[VK_SPACE] = false;

   }else if(inputSystem.keys[VK_ESCAPE]){
      setGameOver();
   }
   
}

void OGLGameEngine::cameraUpdate()
{
  // theCamera->changeThetaPhi(inputSystem.getMouseXRatio(), inputSystem.getMouseYRatio());
   theCamera->animate();
   theCamera->updateTransform();
   gameWorld->updateCamera();
}
