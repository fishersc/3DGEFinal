#include "MyWorld.h"
#include "Sphere.h"
#include "MyCompositeObject.h"
#include "BackForthBehavior.h"
#include "Material.h"
#include "FlatSurface.h"
#include "OGLSphericalCamera.h"
#include "OGLReverseSphericalCamera.h"
#include "OGLGameEngine.h"
#include "FlatSurface.h"
#include "Axis.h"
#include "BoundingBox.h"
#include "LineCuboid.h"
#include "MyCompositeObject.h"
#include "Cylinder.h"
#include "RandomWaypointBehavior.h"
#include "SimpleHitBehavior.h"
#include "SpaceShip.h"
#include "Astroid.h"
#include "Laser.h"


#include <glm/gtc/type_ptr.hpp>
#include <glutil/glutil.h>
#include <sstream>

MyWorld::MyWorld(OGLGameEngine* gameEngine) : OGLGameWorld(gameEngine)
{
   lightSpeed = 0;
   count = 0;
   rateCount = 0;
}

MyWorld::~MyWorld(void)
{
}

void MyWorld::animate(float durationMS)
{
   OGLGameWorld::animate(durationMS);
   checkForCollisions();
   showBoundingBoxes();


   //Astroid* asteroid =  (Astroid*)objects["GiantAstroid"];
   //asteroid->base->frame.translate(.01f,0,0);


   Laser* laser = NULL;
   SpaceShip* ship = (SpaceShip*)objects["ship"];
   std::map<string, AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++)
   {
	   laser = dynamic_cast<Laser*>((*io).second);
	   if(laser != NULL)
	   {
		   if(laser->frame.getPosition().z < -zFar + ship->body->frame.getPosition().z) 
		   {
			   io--;
			   objects.erase(laser->name);
			   rateCount--;
			   if(io == objects.end()) break;
		   }
	   }
   }

   Astroid* astroid;
   if(ship->body->frame.getPosition().z < -1000)
   {
	   for(io = objects.begin(); io != objects.end(); io++)
	   {
		   astroid = dynamic_cast<Astroid*>((*io).second);
		   if(astroid != NULL)
		   {
				   io--;
				   objects.erase(astroid->name);
				   if(io == objects.end()) break;
		   }
	   }
	   createAstroids();
   }

}

void MyWorld::checkForCollisions()
{



   BoundingBox b1, b2;
   Laser* laser = NULL;
   /*
   std::map<string, AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++)
   {
	   laser = dynamic_cast<Laser*>((*io).second);
	   if(laser != NULL)
	   {
		   laser->useBoundingBox = true;
		   laser->getOrientedBoundingBox(.3, .3, 2);
	   }
   }
   */
   Astroid * astroid = NULL;
   std::map<string, AbstractGameObject*>::iterator io,io2;

   for(io2= objects.begin(); io2 != objects.end(); io2++)
   {
	   astroid = dynamic_cast<Astroid*>((*io2).second);
	   if(astroid != NULL)
	   {
		   astroid->useBoundingBox = true;
		   b2= astroid->getOrientedBoundingBox(sqrt(2.0f*(astroid->size*astroid->size)), sqrt(2.0f*(astroid->size*astroid->size)), sqrt(2.0f*(astroid->size*astroid->size)));
		   b2.orientation = astroid->base->frame.orientation;
		   for(io = objects.begin(); io != objects.end(); io++)
		   {
			   laser = dynamic_cast<Laser*>((*io).second);
			   if(laser != NULL)
			   {
				   laser->useBoundingBox = true;
				   b1 = laser->getOrientedBoundingBox(.3, .3, 2);
				   if(b1.overlapsWith(b2))
				   {
					   astroid->base->frame.setPosition(glm::vec3(-10,5,0));
				   }
			   }
		   }
	   }
	}


   // THIS CODE IS FOR REFERENCE s
   /*std::map<string, AbstractGameObject*>::iterator io1, io2;
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
   }*/
}

void MyWorld::showBoundingBoxes()
{
   for(int i = 0; i < (int)boxes.size(); i++){
      delete boxes[i];
   }
   boxes.clear();

   BoundingBox b;
   LineCuboid* lc = NULL;

   AbstractGameObject* object = NULL;
   std::map<string, AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      object = (*io).second;
      b = object->getOrientedBoundingBox();




      lc = new LineCuboid(b.getWidth(), b.getHeight(), b.getDepth());
      if(object->objectsHit.size() == 0){
         lc->vertexData.setToOneColor(0, 1, 0);
      }
      else{
         lc->vertexData.setToOneColor(1, 0, 0);
      }
      lc->generateVBO();
      lc->setShader(shaderMan.shaders["no light"].shaderProgram);
      lc->setTransformMatrixUniform(shaderMan.shaders["no light"].unifs["localToWorldMatrix"]);
      lc->frame = object->frame;
      lc->frame.setPosition(b.getCenter());
      boxes.push_back(lc);


   }

	Astroid* ast = NULL;
	for(io = objects.begin(); io != objects.end(); io++)
   {
	    ast = dynamic_cast<Astroid*>((*io).second);
	   if(ast != NULL)
	   {
		   ast = dynamic_cast<Astroid*>((*io).second);
			 ast->useBoundingBox = true;
			 b=  ast->getOrientedBoundingBox(sqrt(2.0f*(ast->size*ast->size)), sqrt(2.0f*(ast->size*ast->size)), sqrt(2.0f*(ast->size*ast->size)));  //set to astroid width, height, depth
	   
			  lc = new LineCuboid(b.getWidth(), b.getHeight(), b.getDepth());
				if(object->objectsHit.size() == 0){
			 lc->vertexData.setToOneColor(0, 1, 0);
		  }
		  else{
			 lc->vertexData.setToOneColor(0, 0, 1);
		  }
			  lc->generateVBO();
		  lc->setShader(shaderMan.shaders["no light"].shaderProgram);
		  lc->setTransformMatrixUniform(shaderMan.shaders["no light"].unifs["localToWorldMatrix"]);
		  lc->frame = object->frame;
			lc->frame.setPosition(ast->base->frame.getPosition());
		  boxes.push_back(lc);
	   }
   }


    Laser* laser = NULL;
   for(io = objects.begin(); io != objects.end(); io++)
   {
	    laser = dynamic_cast<Laser*>((*io).second);
	   if(laser != NULL)
	   {
		   laser = dynamic_cast<Laser*>((*io).second);
			 laser->useBoundingBox = true;
			b=  laser->getOrientedBoundingBox(.3, .3, 2.1);
	   
			  lc = new LineCuboid(b.getWidth(), b.getHeight(), b.getDepth());
				if(object->objectsHit.size() == 0){
			 lc->vertexData.setToOneColor(0, 1, 0);
		  }
		  else{
			 lc->vertexData.setToOneColor(0, 0, 1);
		  }
			  lc->generateVBO();
		  lc->setShader(shaderMan.shaders["no light"].shaderProgram);
		  lc->setTransformMatrixUniform(shaderMan.shaders["no light"].unifs["localToWorldMatrix"]);
		  lc->frame = object->frame;
		  lc->frame.setPosition(b.getCenter());
		  boxes.push_back(lc);
	   }
   }
}

void MyWorld::render()
{
   for(int i = 0; i < (int)boxes.size(); i++){
      boxes[i]->render();
   }
   OGLGameWorld::render();
}

void MyWorld::updateCamera()
{
   OGLSphericalCamera* camera = ((OGLGameEngine*)gameEngine)->theCamera;

   SpaceShip* s = (SpaceShip*)objects["ship"]; //Comment out these two lines to make camera still if you need to
   camera->position.z = s->body->frame.getPosition().z + 13;

   // Iterate over all the shaders
   map<string, OGLShaderManager::ShaderData>::iterator si;
   for(si = shaderMan.shaders.begin(); si != shaderMan.shaders.end(); si++){
      glUseProgram((*si).second.shaderProgram);
      glUniformMatrix4fv((*si).second.unifs["worldToCameraMatrix"], 1, GL_FALSE, glm::value_ptr(camera->transformMatrix));
	   glUseProgram(0);
   }

   // Send the camera position to the shader for use in the specular highlights
   glUseProgram(shaderMan.shaders["world lighting"].shaderProgram);
   glUniform3fv(shaderMan.shaders["world lighting"].unifs["worldCameraPos"], 1, glm::value_ptr(camera->position));
	glUseProgram(0);
}

void MyWorld::updateViewport(float aspectRatio)
{
	glutil::MatrixStack persMatrix;
	persMatrix.Perspective(60.0f, aspectRatio, zNear, zFar);

   // Iterate over all the shaders
   map<string, OGLShaderManager::ShaderData>::iterator si;
   for(si = shaderMan.shaders.begin(); si != shaderMan.shaders.end(); si++){
      glUseProgram((*si).second.shaderProgram);
      glUniformMatrix4fv((*si).second.unifs["cameraToClipMatrix"], 1, GL_FALSE, glm::value_ptr(persMatrix.Top()));
   }
   glUseProgram(0);
}

void MyWorld::doWorldEvent(int number, float durationMS)
{
   OGLSphericalCamera* camera = ((OGLGameEngine*)gameEngine)->theCamera;
   SpaceShip* ship = (SpaceShip*)objects["ship"];

   switch(number){
      case 100:
		  if(ship->speed < ship->MaxSpeed)
			 ship -> speed += .001f;
         //camera->position += (camera->lookDir * 10.0f * durationMS/1000.0f);
         //camera->position.y = 10;
         break;
      case 101:
		  if(ship->speed > 0)
			 ship -> speed -= .001f;
		  else
			  ship->speed =0;
         //camera->position -= (camera->lookDir * 10.0f * durationMS/1000.0f);
        // camera->position.y = 10;
         break;
	  case 102:
		  if(ship->strafePOS < ship->LimitStrafe)
		  {
			 ship->strafe += .03f;
			 ship->strafePOS += .03f;
		  }
		  break;
	  case 103:
		  if(ship->strafePOS > -ship->LimitStrafe)
		  {
			ship->strafe -= .03f;
			ship->strafePOS -= .03f;
		  }
		  break;
	  case 300:
		  fireLaser();
		  break;
   }
}

void MyWorld::fireLaser()
{
	SpaceShip* ship = (SpaceShip*)objects["ship"];
	
	stringstream a;
	a << count-1;
	if(rateCount == 0 || objects[a.str()] == NULL || objects[a.str()]->frame.getPosition().z < -zFar/3 + ship->body->frame.getPosition().z)
	{

	stringstream ss;
	ss << count;
	count++;
	rateCount++;

	//add speed of ship
	//FUnky stuff happened when i added the speed to the laser speed so... yeah.
	Laser* laser = new Laser(0.8f+ship->speed);
	laser->useBoundingBox = true;
	laser->material.setDiffuse(1, 0, 0);
	laser->material.setAmbient(0.6f, 0.6f, 0.6f);
	laser->vertexData.setToOneColor(laser->material.getDiffuse().r, laser->material.getDiffuse().g, laser->material.getDiffuse().b);
	laser->generateVBO();

	//laser->fire(ship->gun + ship->body->frame.getPosition(), ship->body->frame);
	
	//Puts Laser in center of ship
	laser->fire(ship->body->frame.getPosition(), ship->body->frame);
	
	laser->name = ss.str();

	laser->setShader(shaderMan.shaders["world lighting"].shaderProgram);
	laser->setTransformMatrixUniform(shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"]);
     laser->setAmbientIntensityUniform(shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"]);
         laser->setSpecularUniform(shaderMan.shaders["world lighting"].unifs["fragSpecular"]);
         laser->setShininessUniform(shaderMan.shaders["world lighting"].unifs["fragShininess"]);

		 objects[laser->name] = laser;
	}



}

void MyWorld::createGameObjects()
{
   OGLReverseSphericalCamera* camera = (OGLReverseSphericalCamera*)((OGLGameEngine*)gameEngine)->theCamera;
   camera->position.x = 0;
   camera->position.y = 10;
   camera->position.z = 10;

   light.position = glm::vec4(0, 5.5f, 0, 1);
   light.intensity = glm::vec4(0.8f, 0.8f, 0.8f, 1);


   //BackForthBehavior* behave = new BackForthBehavior();
   //behave->backPoint = glm::vec3(-9, 1, -5);
   //behave->forthPoint = glm::vec3(9, 1, -5);
   //m->behavior = behave;
   //behave->object = m;

  /* RandomWaypointBehavior* behave = new RandomWaypointBehavior(-20, 20, -20, 20, 1);
   m->behavior = behave;
   behave->object = m;*/  

   Material mat;
   mat.setDiffuse(0.1f, 0.5f, 0.2f); 
   mat.setAmbient(0.2f, 0.2f, 0.2f);

   SpaceShip* ship = new SpaceShip(glm::vec3(0, 2, -5));
   ship->material = mat;
   ship->vertexData.setToOneColor(ship->material.getDiffuse().r, ship->material.getDiffuse().g, ship->material.getDiffuse().b);
   ship->generateVBO();
   objects["ship"] = ship;

  createAstroids();

  /* m = new MyCompositeObject(glm::vec3(0, 1, -5));
   m->useBoundingBox = true;
   m->frame.translate(0, 0, 2);
   m->base->material = mat;
   m->base->vertexData.setToOneColor(m->base->material.getDiffuse().r, m->base->material.getDiffuse().g, m->base->material.getDiffuse().b);
   m->base->generateVBO();
   objects["other thing"] = m;

   RandomWaypointBehavior* behave2 = new RandomWaypointBehavior(-20, 20, -20, 20, 1);
   m->behavior = behave2;
   behave2->object = m;
*/
  /* mat.setDiffuse(0.8f, 0.8f, 0.0f); 
   mat.setAmbient(0.5f, 0.5f, 0.0f);
   mat.setSpecular(1.0f, 1.0f, 1.0f);
   mat.setShininess(500);*/

  /* Cylinder* c = new Cylinder(glm::vec3(), 1.0f, 5);
   c->useBoundingBox = true;
   c->material = mat;
   c->vertexData.setToOneColor(c->material.getDiffuse().r, c->material.getDiffuse().g, c->material.getDiffuse().b);
   c->generateVBO();
   c->frame.translate(0, 2.5, -5);
   objects["cylinder"] = c;

   SimpleHitBehavior* shb = new SimpleHitBehavior();
   shb->object = c;
   c->behavior = shb;*/

   Material floorMat;
   floorMat.setDiffuse(0.5f, 0.5f, 0.5f); 
   floorMat.setAmbient(0.2f, 0.2f, 0.2f);
   FlatSurface* floor = new FlatSurface(100, 100, 10, 10);
   floor->material = floorMat;
   floor->vertexData.setToOneColor(floor->material.getDiffuse().r, floor->material.getDiffuse().g, floor->material.getDiffuse().b);
   floor->generateVBO();
   objects["floor"] = floor;
}

void MyWorld::createAstroids()
{
	BoundZ bounds;
      Material mat;
   mat.setDiffuse(0.1f, 0.5f, 0.2f); 
   mat.setAmbient(0.2f, 0.2f, 0.2f);
   SpaceShip* ship = (SpaceShip*)objects["ship"];
//Astroid
   Astroid* GiantAstroid = new Astroid(glm::vec3(-7, 2, -250),7);
   GiantAstroid->material = mat;
   GiantAstroid->vertexData.setToOneColor(GiantAstroid->material.getDiffuse().r, GiantAstroid->material.getDiffuse().g, GiantAstroid->material.getDiffuse().b);
   GiantAstroid->generateVBO();
   bounds = GiantAstroid->checkSector();

   RandomWaypointBehavior* behave = new RandomWaypointBehavior(-300,300,bounds.maxZ,bounds.minZ,2);
   GiantAstroid->base->behavior = behave;
   behave->object = GiantAstroid->base;
   GiantAstroid->name = "GiantAstroid";

   //set up shaders again for when recreating  There has to be a better way to do this then doing it for all the astroids individually
	GiantAstroid->setShader(shaderMan.shaders["world lighting"].shaderProgram);
	GiantAstroid->setTransformMatrixUniform(shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"]);
	GiantAstroid->setAmbientIntensityUniform(shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"]);
	GiantAstroid->setSpecularUniform(shaderMan.shaders["world lighting"].unifs["fragSpecular"]);
	GiantAstroid->setShininessUniform(shaderMan.shaders["world lighting"].unifs["fragShininess"]);

   objects["GiantAstroid"] = GiantAstroid;

//Astroid 1
   Astroid* GiantAstroid1 = new Astroid(glm::vec3(-20, 2, -750),5);
   GiantAstroid1->material = mat;
   GiantAstroid1->vertexData.setToOneColor(GiantAstroid1->material.getDiffuse().r, GiantAstroid1->material.getDiffuse().g, GiantAstroid1->material.getDiffuse().b);
   GiantAstroid1->generateVBO();
   bounds = GiantAstroid1->checkSector();

   RandomWaypointBehavior* behave1 = new RandomWaypointBehavior(-300,300,bounds.maxZ,bounds.minZ,2);
   GiantAstroid1->base->behavior = behave1;
   behave1->object = GiantAstroid1->base;

	GiantAstroid1->setShader(shaderMan.shaders["world lighting"].shaderProgram);
	GiantAstroid1->setTransformMatrixUniform(shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"]);
	GiantAstroid1->setAmbientIntensityUniform(shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"]);
	GiantAstroid1->setSpecularUniform(shaderMan.shaders["world lighting"].unifs["fragSpecular"]);
	GiantAstroid1->setShininessUniform(shaderMan.shaders["world lighting"].unifs["fragShininess"]);

   GiantAstroid1->name = "GiantAstroid1";
   objects["GiantAstroid1"] = GiantAstroid1;

//Astroid 2
   Astroid* GiantAstroid2 = new Astroid(glm::vec3(7, 2, 0),3);
   GiantAstroid2->material = mat;
   GiantAstroid2->vertexData.setToOneColor(GiantAstroid2->material.getDiffuse().r, GiantAstroid2->material.getDiffuse().g, GiantAstroid2->material.getDiffuse().b);
   GiantAstroid2->generateVBO();
   GiantAstroid2->name = "GiantAstroid2";

   RandomWaypointBehavior* behave2 = new RandomWaypointBehavior(-300,300,bounds.maxZ,bounds.minZ,2);
   GiantAstroid2->base->behavior = behave2;
   behave2->object = GiantAstroid2->base;

   GiantAstroid2->setShader(shaderMan.shaders["world lighting"].shaderProgram);
	GiantAstroid2->setTransformMatrixUniform(shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"]);
	GiantAstroid2->setAmbientIntensityUniform(shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"]);
	GiantAstroid2->setSpecularUniform(shaderMan.shaders["world lighting"].unifs["fragSpecular"]);
	GiantAstroid2->setShininessUniform(shaderMan.shaders["world lighting"].unifs["fragShininess"]);

   objects["GiantAstroid2"] = GiantAstroid2;

//Astroid 3
    Astroid* GiantAstroid3 = new Astroid(glm::vec3(15, 2, 250),7);
   GiantAstroid3->material = mat;
   GiantAstroid3->vertexData.setToOneColor(GiantAstroid3->material.getDiffuse().r, GiantAstroid3->material.getDiffuse().g, GiantAstroid3->material.getDiffuse().b);
   GiantAstroid3->generateVBO();
   GiantAstroid3->name = "GiantAstroid3";

   RandomWaypointBehavior* behave3 = new RandomWaypointBehavior(-300,300,bounds.maxZ,bounds.minZ,2);
   GiantAstroid3->base->behavior = behave3;
   behave3->object = GiantAstroid3->base;

   GiantAstroid3->setShader(shaderMan.shaders["world lighting"].shaderProgram);
	GiantAstroid3->setTransformMatrixUniform(shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"]);
	GiantAstroid3->setAmbientIntensityUniform(shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"]);
	GiantAstroid3->setSpecularUniform(shaderMan.shaders["world lighting"].unifs["fragSpecular"]);
	GiantAstroid3->setShininessUniform(shaderMan.shaders["world lighting"].unifs["fragShininess"]);

   objects["GiantAstroid3"] = GiantAstroid3;

//Astroid 4
    Astroid* GiantAstroid4 = new Astroid(glm::vec3(2, 2, 750),10);
   GiantAstroid4->material = mat;
   GiantAstroid4->vertexData.setToOneColor(GiantAstroid4->material.getDiffuse().r, GiantAstroid4->material.getDiffuse().g, GiantAstroid4->material.getDiffuse().b);
   GiantAstroid4->generateVBO();
   GiantAstroid4->name = "GiantAstroid4";

   RandomWaypointBehavior* behave4 = new RandomWaypointBehavior(-300,300,bounds.maxZ,bounds.minZ,2);
   GiantAstroid4->base->behavior = behave4;
   behave4->object = GiantAstroid4->base;

   GiantAstroid4->setShader(shaderMan.shaders["world lighting"].shaderProgram);
	GiantAstroid4->setTransformMatrixUniform(shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"]);
	GiantAstroid4->setAmbientIntensityUniform(shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"]);
	GiantAstroid4->setSpecularUniform(shaderMan.shaders["world lighting"].unifs["fragSpecular"]);
	GiantAstroid4->setShininessUniform(shaderMan.shaders["world lighting"].unifs["fragShininess"]);

   objects["GiantAstroid4"] = GiantAstroid4;

}

void MyWorld::setupShaders()
{
   OGLGameObject* object = NULL;
   shaderMan.addShader("no light", "vertex_source_no_light.glsl", "fragment_source_simple.glsl");
	shaderMan.compileShaderProgram("no light");
   glBindAttribLocation(shaderMan.shaders["no light"].fragmentShader, 0, "position");
   glBindAttribLocation(shaderMan.shaders["no light"].fragmentShader, 1, "vertexColor");
   glBindAttribLocation(shaderMan.shaders["no light"].fragmentShader, 2, "vertexNormal");
	shaderMan.linkShaderProgram("no light");
  /* object = (OGLGameObject*)objects["light"];
   object->setShader(shaderMan.shaders["no light"].shaderProgram);
   object = (OGLGameObject*)objects["axis"];
   object->setShader(shaderMan.shaders["no light"].shaderProgram);*/
     
   shaderMan.addShader("world lighting", "vertex_source_fragment_lighting.glsl", "fragment_source_fragment_lighting.glsl");
	shaderMan.compileShaderProgram("world lighting");
	glBindAttribLocation(shaderMan.shaders["world lighting"].fragmentShader, 0, "position");
	glBindAttribLocation(shaderMan.shaders["world lighting"].fragmentShader, 1, "vertexColor");
   glBindAttribLocation(shaderMan.shaders["world lighting"].fragmentShader, 2, "vertexNormal");
	shaderMan.linkShaderProgram("world lighting");
   std::map<string, AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      if((*io).first != "light" && (*io).first != "axis"){
         object = (OGLGameObject*)(*io).second;
         object->setShader(shaderMan.shaders["world lighting"].shaderProgram);
      }
   }

   GLuint shader = shaderMan.shaders["no light"].shaderProgram;
   shaderMan.shaders["no light"].unifs["cameraToClipMatrix"] = glGetUniformLocation(shader, "cameraToClipMatrix");
   shaderMan.shaders["no light"].unifs["worldToCameraMatrix"] = glGetUniformLocation(shader, "worldToCameraMatrix");
   shaderMan.shaders["no light"].unifs["localToWorldMatrix"] = glGetUniformLocation(shader, "localToWorldMatrix");
   /*object = (OGLGameObject*)objects["light"];
   object->setTransformMatrixUniform(shaderMan.shaders["no light"].unifs["localToWorldMatrix"]);
   object = (OGLGameObject*)objects["axis"];
   object->setTransformMatrixUniform(shaderMan.shaders["no light"].unifs["localToWorldMatrix"]);*/

   shader = shaderMan.shaders["world lighting"].shaderProgram;
   shaderMan.shaders["world lighting"].unifs["worldGlobalLightPos"] = glGetUniformLocation(shader, "worldGlobalLightPos");
   shaderMan.shaders["world lighting"].unifs["globalLightIntensity"] = glGetUniformLocation(shader, "globalLightIntensity");
   shaderMan.shaders["world lighting"].unifs["worldLightPos"] = glGetUniformLocation(shader, "worldLightPos");
   shaderMan.shaders["world lighting"].unifs["worldCameraPos"] = glGetUniformLocation(shader, "worldCameraPos");
   shaderMan.shaders["world lighting"].unifs["lightIntensity"] = glGetUniformLocation(shader, "lightIntensity");
   shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"] = glGetUniformLocation(shader, "fragAmbientIntensity");
   shaderMan.shaders["world lighting"].unifs["fragSpecular"] = glGetUniformLocation(shader, "fragSpecular");
   shaderMan.shaders["world lighting"].unifs["fragShininess"] = glGetUniformLocation(shader, "fragShininess");
   shaderMan.shaders["world lighting"].unifs["cameraToClipMatrix"] = glGetUniformLocation(shader, "cameraToClipMatrix");
   shaderMan.shaders["world lighting"].unifs["worldToCameraMatrix"] = glGetUniformLocation(shader, "worldToCameraMatrix");
   shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"] = glGetUniformLocation(shader, "localToWorldMatrix");
   for(io = objects.begin(); io != objects.end(); io++){
      if((*io).first != "light" && (*io).first != "axis"){
         object = (OGLGameObject*)(*io).second;
         object->setTransformMatrixUniform(shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"]);
         object->setAmbientIntensityUniform(shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"]);
         object->setSpecularUniform(shaderMan.shaders["world lighting"].unifs["fragSpecular"]);
         object->setShininessUniform(shaderMan.shaders["world lighting"].unifs["fragShininess"]);
      }
   }
}


void MyWorld::setupLights()
{
   glUseProgram(shaderMan.shaders["world lighting"].shaderProgram);
   glUniform4fv(shaderMan.shaders["world lighting"].unifs["lightIntensity"], 1, glm::value_ptr(light.intensity));
   glUniform4f(shaderMan.shaders["world lighting"].unifs["globalLightIntensity"], 0.4f, 0.4f, 0.4f, 1.0f);
   glUniform3fv(shaderMan.shaders["world lighting"].unifs["worldGlobalLightPos"], 1, glm::value_ptr(lightDirection));
   glUniform4fv(shaderMan.shaders["world lighting"].unifs["worldLightPos"], 1, glm::value_ptr(light.position));
	glUseProgram(0);
}