#include "OGLGameWorld.h"
#include "OGLGameEngine.h"
#include "OGLSphericalCamera.h"
#include "Material.h"
#include "AbstractGameObject.h"
#include "BoundingBox.h"

OGLGameWorld::OGLGameWorld(OGLGameEngine* gameEngine) : AbstractGameWorld((GameEngine*)gameEngine)
{
   zNear = 0.1f; 
	zFar = 112.0f;
   // The default light direction is directly above
   lightDirection = glm::vec4(0.0f, 0.0f, 14.0f, 0.0f);
}

OGLGameWorld::~OGLGameWorld(void)
{
}

void OGLGameWorld::initialize()
{
   glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

   createGameObjects();

   setupShaders();

   setupLights();

   glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); 
	glFrontFace(GL_CCW);

   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
   glDepthFunc(GL_LEQUAL);
   glDepthRange(0.0f, 1.0f);
}


void OGLGameWorld::update()
{
   std::map<string, AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      (*io).second->update();
   }
}

void OGLGameWorld::animate(float durationMS)
{
   std::map<string, AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      (*io).second->animate(durationMS);
   }
}

void OGLGameWorld::render()
{
   std::map<string, AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      (*io).second->render();
   }
}

void  OGLGameWorld::checkForCollisions()
{
   AbstractGameObject* obj1;
   AbstractGameObject* obj2;
   BoundingBox b1, b2;
   std::map<string, AbstractGameObject*>::iterator io1, io2;
   for(io1 = objects.begin(); io1 != objects.end(); io1++){
      obj1 = (*io1).second;
      obj1->objectsHit.clear();
      b1 = obj1->getOrientedBoundingBox();
      for(io2 = objects.begin(); io2 != objects.end(); io2++){
         obj2 = (*io2).second;
         if(obj2 == obj1) continue;
         b2 = obj2->getOrientedBoundingBox();
         if(b1.overlapsWith(b2)){
            obj1->objectsHit.push_back(obj2);
         }
      }
   }
}



