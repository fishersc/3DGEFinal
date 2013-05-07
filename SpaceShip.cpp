#include "SpaceShip.h"


SpaceShip::SpaceShip(const glm::vec3& pos)
{
   body = new Cuboid(pos, 5, 1, 10);
    body->material.setDiffuse(1, 1, 1); 
   body->material.setAmbient(0.6f, 0.6f, 0);
   body->vertexData.setToOneColor(body->material.getDiffuse().r, body->material.getDiffuse().g, body->material.getDiffuse().b);
   body->generateVBO();

   engineConnector1 = new Cuboid(pos, 2, 1, 1);
	engineConnector1->material.setDiffuse(1, 1, 1); 
   engineConnector1->material.setAmbient(0.6f, 0.6f, 0);
   engineConnector1->vertexData.setToOneColor(engineConnector1->material.getDiffuse().r,  engineConnector1->material.getDiffuse().g,  engineConnector1->material.getDiffuse().b);
   engineConnector1->generateVBO();

   engineConnector2 = new Cuboid(pos, 2, 1, 1);
   engineConnector2->material.setDiffuse(1, 1, 1); 
   engineConnector2->material.setAmbient(0.6f, 0.6f, 0);
   engineConnector2->vertexData.setToOneColor(engineConnector2->material.getDiffuse().r,  engineConnector2->material.getDiffuse().g,  engineConnector2->material.getDiffuse().b);
   engineConnector2->generateVBO();

   engine1 = new Cylinder(pos, 0.7f, 4.0f, 14, 8);
    engine1->material.setDiffuse(1, 1, 1); 
   engine1->material.setAmbient(0.6f, 0.6f, 0);
   engine1->vertexData.setToOneColor(engine1->material.getDiffuse().r,  engine1->material.getDiffuse().g,  engine1->material.getDiffuse().b);
   engine1->generateVBO();

  engine2 = new Cylinder(pos, 0.7f, 4.0f, 14, 8);
  engine2->material.setDiffuse(1, 1, 1); 
   engine2->material.setAmbient(0.6f, 0.6f, 0);
   engine2->vertexData.setToOneColor(engine2->material.getDiffuse().r,  engine2->material.getDiffuse().g,  engine2->material.getDiffuse().b);
   engine2->generateVBO();

   
   spoilerside2 = new Cuboid(pos, 2, 1, 1);
    spoilerside2->material.setDiffuse(1, 1, 1); 
   spoilerside2->material.setAmbient(0.6f, 0.6f, 0);
    spoilerside2->vertexData.setToOneColor(spoilerside2->material.getDiffuse().r,  spoilerside2->material.getDiffuse().g,  spoilerside2->material.getDiffuse().b);
   spoilerside2->generateVBO();

    spoilertop = new Cuboid(pos, 2, 1, 1);
    spoilertop->material.setDiffuse(1, 1, 1); 
   spoilertop->material.setAmbient(0.6f, 0.6f, 0);
    spoilertop->vertexData.setToOneColor(spoilertop->material.getDiffuse().r,  spoilertop->material.getDiffuse().g,  spoilertop->material.getDiffuse().b);
   spoilertop->generateVBO();


   spoilerside1 = new Cuboid(pos, 3, 0.5f, 1);
    spoilerside1->material.setDiffuse(1, 1, 1); 
   spoilerside1->material.setAmbient(0.6f, 0.6f, 0);
    spoilerside1->vertexData.setToOneColor(spoilerside1->material.getDiffuse().r,  spoilerside1->material.getDiffuse().g,  spoilerside1->material.getDiffuse().b);
   spoilerside1->generateVBO();

  /*thruster1 = new Pyramid();
  thruster1->material.setDiffuse(1, 1, 1); 
   thruster1->material.setAmbient(0.6f, 0.6f, 0);
   thruster1->vertexData.setToOneColor(thruster1->material.getDiffuse().r,  thruster1->material.getDiffuse().g,  thruster1->material.getDiffuse().b);
   thruster1->generateVBO();

  thruster2 = new Pyramid();
  thruster2->material.setDiffuse(1, 1, 1); 
   thruster2->material.setAmbient(0.6f, 0.6f, 0);
   thruster2->vertexData.setToOneColor(thruster2->material.getDiffuse().r,  thruster2->material.getDiffuse().g,  thruster2->material.getDiffuse().b);
   thruster2->generateVBO();

  cockpit1 = new Pyramid();
  cockpit1->material.setDiffuse(1, 1, 1); 
   cockpit1->material.setAmbient(0.6f, 0.6f, 0);
   cockpit1->vertexData.setToOneColor(cockpit1->material.getDiffuse().r,  cockpit1->material.getDiffuse().g,  cockpit1->material.getDiffuse().b);
   cockpit1->generateVBO();*/

  cockpit2 = new Sphere(glm::vec3(0,0,0), 1.6, 20, 8);
   cockpit2->material.setDiffuse(0.7f, 0.7f, 0.7f); 
   cockpit2->material.setAmbient(224, 223, 219);
   cockpit2->material.setShininess(1.0f);
   cockpit2->vertexData.setToOneColor(cockpit2->material.getDiffuse().r,  cockpit2->material.getDiffuse().g,  cockpit2->material.getDiffuse().b);
   cockpit2->generateVBO();

   angleY = 0;
   angleZ = 0;
   speedZ = 60;

   MaxSpeed =1.50f;
   speed = 0.5f;
   LimitStrafe = 10;  //how far can strafe left or right from center

   strafe = 0;
   strafePOS= 0;
  // speed = 0;
}


SpaceShip::~SpaceShip(void)
{
   delete body;
   delete engineConnector1;
   delete engineConnector2;
   delete engine1;
   delete engine2;
   delete spoilerside1;
   delete spoilerside2;
   delete spoilertop;
  //delete thruster1;
 // delete thruster2;
   //delete cockpit1;
    delete cockpit2;
}

void SpaceShip::update()
{
	body->frame.translate(strafe,0,-speed);
	strafe = 0;

	//Loops the ship
	if(body->frame.getPosition().z < -300)
	{
		glm::vec3 resetPOS = glm::vec3(body->frame.getPosition().x,body->frame.getPosition().y,300);
		body->frame.setPosition(resetPOS);
	}
	
}

void SpaceShip::animate(float durationMS)
{
	
	/*
   angleY += (30 * durationMS/1000);
   if(angleY > 360) angleY -= 360;
   angleZ += (speedZ * durationMS/1000);
   if(angleZ > 45){
      speedZ = -60;
   }
   else if(angleZ < -45){
      speedZ = 60;
   }
   */
}

void SpaceShip::setTransformMatrixUniform(GLuint unif)
{
   body->setTransformMatrixUniform(unif);
   engineConnector1->setTransformMatrixUniform(unif);
   engineConnector2->setTransformMatrixUniform(unif);
	spoilerside1->setTransformMatrixUniform(unif);
	spoilerside2->setTransformMatrixUniform(unif);
	spoilertop->setTransformMatrixUniform(unif);
  /* thruster1->setTransformMatrixUniform(unif);
   thruster2->setTransformMatrixUniform(unif);*/
  engine1->setTransformMatrixUniform(unif);
  engine2->setTransformMatrixUniform(unif);
  // cockpit1->setTransformMatrixUniform(unif);
   cockpit2->setTransformMatrixUniform(unif);
}
void SpaceShip::setAmbientIntensityUniform(GLuint unif)
{
  body->setAmbientIntensityUniform(unif);
   engineConnector1->setAmbientIntensityUniform(unif);
   engineConnector2->setAmbientIntensityUniform(unif);
   spoilerside1->setAmbientIntensityUniform(unif);
	spoilerside2->setAmbientIntensityUniform(unif);
	spoilertop->setAmbientIntensityUniform(unif);
   /*thruster1->setAmbientIntensityUniform(unif);
   thruster2->setAmbientIntensityUniform(unif);*/
    engine1->setAmbientIntensityUniform(unif);
  engine2->setAmbientIntensityUniform(unif);
  // cockpit1->setAmbientIntensityUniform(unif);
   cockpit2->setAmbientIntensityUniform(unif);
}

void  SpaceShip::setSpecularUniform(GLuint unif)
{
   
body->setSpecularUniform(unif);
   engineConnector1->setSpecularUniform(unif);
   engineConnector2->setSpecularUniform(unif);
   spoilerside1->setSpecularUniform(unif);
	spoilerside2->setSpecularUniform(unif);
	spoilertop->setSpecularUniform(unif);
  /* thruster1->setSpecularUniform(unif);
   thruster2->setSpecularUniform(unif);*/
    engine1->setSpecularUniform(unif);
  engine2->setSpecularUniform(unif);
   //cockpit1->setSpecularUniform(unif);
   cockpit2->setSpecularUniform(unif);
}

void  SpaceShip::setShininessUniform(GLuint unif)
{
  
  body->setShininessUniform(unif);
   engineConnector1->setShininessUniform(unif);
   engineConnector2->setShininessUniform(unif);
    spoilerside1->setShininessUniform(unif);
	spoilerside2->setShininessUniform(unif);
	spoilertop->setShininessUniform(unif);
   /*thruster1->setShininessUniform(unif);
   thruster2->setShininessUniform(unif);*/
    engine1->setShininessUniform(unif);
  engine2->setShininessUniform(unif);
   //cockpit1->setShininessUniform(unif);
   cockpit2->setShininessUniform(unif);
}

void SpaceShip::setShader(GLuint shader)
{
  
   body->setShader(shader);
   engineConnector1->setShader(shader);
   engineConnector2->setShader(shader);
   spoilerside1->setShader(shader);
	spoilerside2->setShader(shader);
	spoilertop->setShader(shader);
  /* thruster1->setShader(shader);
   thruster2->setShader(shader);*/
    engine1->setShader(shader);
  engine2->setShader(shader);
  // cockpit1->setShader(shader);
   cockpit2->setShader(shader);
}

void SpaceShip::render()
{
   frameStack.setBaseFrame(body->frame);
  gun = glm::vec3(body->frame.orientation* glm::vec4(0, 0, 1, 1));
 // * glm::vec4(3.5f, 0, 3.5f, 1)
   body->render();
   frameStack.push();
   {
      frameStack.translate(3.5f, 0, -1.0f);
      engineConnector1->render(frameStack.top());
	
   }
   frameStack.pop();

    frameStack.push();
   {
      frameStack.translate(1.5f, 2.0, 5.1f);
	  frameStack.rotateZ(-90);
	  frameStack.rotateY(30);
      spoilerside1->render(frameStack.top());
	
   }
   frameStack.pop();



   frameStack.push();
      {
         frameStack.translate(-3.5f, 0, -1.0f);
		 engineConnector2->render(frameStack.top());
      }
      frameStack.pop();

	  frameStack.push();
      {
         frameStack.translate(5.0f, 0, -1.0f);
		 frameStack.rotateX(90);
		 engine1->render(frameStack.top());
      }
      frameStack.pop();

	  frameStack.push();
      {
         frameStack.translate(-5.0f, 0, -1.0);
		 frameStack.rotateX(90);
		 engine2->render(frameStack.top());
      }
      frameStack.pop();


	 /* frameStack.push();
      {
		  frameStack.rotateX(-90);
          frameStack.translate(0,3.0f, 2.75f);
		
		 cockpit1->render(frameStack.top());
      }
      frameStack.pop();*/

	  frameStack.push();
      {
          frameStack.translate(0,0.75f, -1.0f);
		
		 cockpit2->render(frameStack.top());
      }
      frameStack.pop();

	 /* frameStack.push();
      {
		  frameStack.rotateX(-90);
          frameStack.translate(5.0f,-5.0f, 2.0f);
		
		 thruster1->render(frameStack.top());
      }
      frameStack.pop();

	   frameStack.push();
      {
		  frameStack.rotateX(-90);
          frameStack.translate(-5.0f,-5.0f, 2.0f);
		
		 thruster2->render(frameStack.top());
      }
      frameStack.pop();
	  */

	  
}