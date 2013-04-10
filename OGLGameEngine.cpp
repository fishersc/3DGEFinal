#include "Windows.h"
#include "OGLGameEngine.h"
#include "OGLSphericalCamera.h"
#include "OGLReverseSphericalCamera.h"
#include "OGLGameWorld.h"

#include <iostream>

OGLGameEngine::OGLGameEngine(void)
{
   gameWorld = new OGLGameWorld(this);
   camera = new OGLSphericalCamera();
   camera2 = new OGLReverseSphericalCamera();
   theCamera = (OGLSphericalCamera*)camera;
}

OGLGameEngine::~OGLGameEngine(void)
{
   if(gameWorld) delete gameWorld;
   if(camera2) delete camera2;
}

void OGLGameEngine::initialize()
{
   theCamera->cameraPosSpherical.phi = 0.0f;  
   theCamera->cameraPosSpherical.theta = 0.0f;  
   theCamera->cameraPosSpherical.rho = 20.0f;  

   theCamera->cameraTarget.x = 0;
   theCamera->cameraTarget.y = 0;
   theCamera->cameraTarget.z = 0;

	//object.makeResources();
   gameWorld->initialize();
}

void OGLGameEngine::setAspectRatio(float aspectRatio)
{
	//object.reshapeViewport(aspectRatio);
   gameWorld->updateViewport(aspectRatio);
}

void OGLGameEngine::gameLogic(float tickTimeMS)
{
   gameWorld->update();
   //object.update(tickTimeMS);
   gameWorld->animate(tickTimeMS);
}

void OGLGameEngine::gamePresentation()
{
   //object.render();
   gameWorld->render();
}

void OGLGameEngine::playerUpdate(float tickTimeMS)
{
   if(inputSystem.keys['1']){ 
      theCamera = (OGLSphericalCamera*)camera;
      theCamera->cameraTarget.x = 0;
      theCamera->cameraTarget.y = 0;
      theCamera->cameraTarget.z = 0;
      inputSystem.keys['1'] = false;
   }else if(inputSystem.keys['2']){
      camera2->position = theCamera->position;
      theCamera = (OGLReverseSphericalCamera*)camera2;
      cameraUpdate();
      inputSystem.keys['2'] = false;
   }else if(inputSystem.keys['3']){
      theCamera->cameraPosSpherical.theta += 10.0f;  
      if(theCamera->cameraPosSpherical.theta > 80) theCamera->cameraPosSpherical.theta = 80;
      inputSystem.keys['3'] = false;
   }else if(inputSystem.keys['6']){
      theCamera->cameraPosSpherical.rho -= 0.5f;  
      if(theCamera->cameraPosSpherical.rho < 1) theCamera->cameraPosSpherical.rho = 1;
      inputSystem.keys['6'] = false;
   }else if(inputSystem.keys[VK_UP]){
      if(theCamera == camera2){
         theCamera->position += (theCamera->lookDir * 1.0f * tickTimeMS/1000.0f);
      }
   }else if(inputSystem.keys[VK_DOWN]){
      if(theCamera == camera2){
         theCamera->position -= (theCamera->lookDir * 1.0f * tickTimeMS/1000.0f);
      }
   }else if(inputSystem.keys[VK_ESCAPE]){
      setGameOver();
   }
}

void OGLGameEngine::cameraUpdate()
{
   theCamera->changeThetaPhi(inputSystem.mouseX, inputSystem.mouseY, windowWidth, windowHeight);
   theCamera->animate();
   theCamera->updateTransform();
   //object.updateCamera(theCamera);
   gameWorld->updateCamera();
}



