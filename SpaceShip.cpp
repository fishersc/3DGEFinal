#include "SpaceShip.h"


SpaceShip::SpaceShip(void)
{
   body = new Cuboid(glm::vec3(0, 0, 0), 5, 1, 10);
   engineConnector1 = new Cuboid(glm::vec3(0, 0, 0), 2, 1, 1);
   engineConnector2 = new Cuboid(glm::vec3(0, 0, 0), 2, 1, 1);
   engine1 = new Cuboid(glm::vec3(0, 0, 0), 1, 1, 3);
  engine2 = new Cuboid(glm::vec3(0, 0, 0), 1, 1, 3);
  thruster1 = new Pyramid();
  thruster2 = new Pyramid();
  cockpit1 = new Pyramid();
  cockpit2 = new Cuboid(glm::vec3(0,0,0),1,0.95f,3);
   angleY = 0;
   angleZ = 0;
   speedZ = 60;
}


SpaceShip::~SpaceShip(void)
{
   delete body;
   delete engineConnector1;
   delete engineConnector2;
   delete engine1;
   delete engine2;
  delete thruster1;
  delete thruster2;
   delete cockpit1;
    delete cockpit2;
}

void SpaceShip::update()
{
}

void SpaceShip::animate(float durationMS)
{
	
   angleY += (30 * durationMS/1000);
   if(angleY > 360) angleY -= 360;
   angleZ += (speedZ * durationMS/1000);
   if(angleZ > 45){
      speedZ = -60;
   }
   else if(angleZ < -45){
      speedZ = 60;
   }

}

void SpaceShip::setTransformMatrixUniform(GLuint unif)
{
   body->setTransformMatrixUniform(unif);
   engineConnector1->setTransformMatrixUniform(unif);
   engineConnector2->setTransformMatrixUniform(unif);
   thruster1->setTransformMatrixUniform(unif);
   thruster2->setTransformMatrixUniform(unif);
  engine1->setTransformMatrixUniform(unif);
  engine2->setTransformMatrixUniform(unif);
   cockpit1->setTransformMatrixUniform(unif);
   cockpit2->setTransformMatrixUniform(unif);
}

void SpaceShip::render()
{
   frameStack.setBaseFrame(body->frame);
   body->render();
   frameStack.push();
   {
      frameStack.translate(3.5f, 0, 3.5f);
      engineConnector1->render(frameStack.top());
   }
   frameStack.pop();

   frameStack.push();
      {
         frameStack.translate(-3.5f, 0, 3.5f);
		 engineConnector2->render(frameStack.top());
      }
      frameStack.pop();

	  frameStack.push();
      {
         frameStack.translate(5.0f, 0, 3.5f);
		 engine1->render(frameStack.top());
      }
      frameStack.pop();

	  frameStack.push();
      {
         frameStack.translate(-5.0f, 0, 3.5);
		 engine2->render(frameStack.top());
      }
      frameStack.pop();


	  frameStack.push();
      {
		  frameStack.rotateX(-90);
          frameStack.translate(0,3.0f, 2.75f);
		
		 cockpit1->render(frameStack.top());
      }
      frameStack.pop();

	  frameStack.push();
      {
          frameStack.translate(0,0.75f, -1.0f);
		
		 cockpit2->render(frameStack.top());
      }
      frameStack.pop();

	  frameStack.push();
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


	  
}