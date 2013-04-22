#include "Astroid.h"
#include "AbstractBehavior.h"


Astroid::Astroid(const glm::vec3& pos)
{
   base = new Cuboid(pos, 7,7, 7);
   base->material.setDiffuse(1, 1, 1); 
   base->material.setAmbient(0.6f, 0.6f, 0.6f);
   base->vertexData.setToOneColor(base->material.getDiffuse().r, base->material.getDiffuse().g, base->material.getDiffuse().b);
   base->generateVBO();

   ast = new Cuboid(pos, 7, 7,7);
   ast->material.setDiffuse(1, 1, 1); 
   ast->material.setAmbient(0.6f, 0.6f, 0.6f);
   ast->vertexData.setToOneColor(base->material.getDiffuse().r, base->material.getDiffuse().g, base->material.getDiffuse().b);
   ast->generateVBO();

    roid = new Cuboid(pos, 7, 7, 7);
   roid->material.setDiffuse(1, 1, 1); 
    roid->material.setAmbient(0.6f, 0.6f, 0.6f);
    roid->vertexData.setToOneColor(base->material.getDiffuse().r, base->material.getDiffuse().g, base->material.getDiffuse().b);
   roid->generateVBO();

   torso = new Cuboid(glm::vec3(0, 0, 0), 7, 7, 7);
   torso->material.setDiffuse(1, 1, 1); 
   torso->material.setAmbient(0.6f, 0.6f, 0.6f);
   torso->vertexData.setToOneColor(torso->material.getDiffuse().r, torso->material.getDiffuse().g, torso->material.getDiffuse().b);
   torso->generateVBO();

   turret = new Cuboid(glm::vec3(0, 0, 0), 7, 7, 7);
   turret->material.setDiffuse(1, 1, 1); 
   turret->material.setAmbient(0.6f, 0.6f, 0.6f);
   turret->vertexData.setToOneColor(turret->material.getDiffuse().r, turret->material.getDiffuse().g, turret->material.getDiffuse().b);
   turret->generateVBO();

   angleY = 0;
   angleZ = 0;
   speedZ = 60;
}


Astroid::~Astroid(void)
{
   delete base;
   delete torso;
   delete turret;
   delete ast;
   delete roid;
}

void Astroid::update()
{
   if(base->behavior){
      base->behavior->updateState();
   }
}

void Astroid::animate(float durationMS)
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

   
   if(base->behavior){
      base->behavior->animate(durationMS);
   }
   */
} 

void Astroid::setTransformMatrixUniform(GLuint unif)
{
   base->setTransformMatrixUniform(unif);
   torso->setTransformMatrixUniform(unif);
   turret->setTransformMatrixUniform(unif);
   ast->setTransformMatrixUniform(unif);
   roid->setTransformMatrixUniform(unif);
}

void Astroid::setAmbientIntensityUniform(GLuint unif)
{
   base->setAmbientIntensityUniform(unif);
   torso->setAmbientIntensityUniform(unif);
   turret->setAmbientIntensityUniform(unif);
   ast->setAmbientIntensityUniform(unif);
   roid->setAmbientIntensityUniform(unif);
}

void  Astroid::setSpecularUniform(GLuint unif)
{
   base->setSpecularUniform(unif);
   torso->setSpecularUniform(unif);
   turret->setSpecularUniform(unif);
    ast->setSpecularUniform(unif);
	 roid->setSpecularUniform(unif);
}

void  Astroid::setShininessUniform(GLuint unif)
{
   base->setShininessUniform(unif);
   torso->setShininessUniform(unif);
   turret->setShininessUniform(unif);
    ast->setShininessUniform(unif);
	 roid->setShininessUniform(unif);
}

void Astroid::setShader(GLuint shader)
{
   base->setShader(shader);
   torso->setShader(shader);
   turret->setShader(shader);
   ast->setShader(shader);
   roid->setShader(shader);
}

void Astroid::render()
{
   frameStack.setBaseFrame(base->frame);
   base->render();
   frameStack.push();
   {
      
      frameStack.rotateY(25);
	   frameStack.rotateX(35);
      torso->render(frameStack.top());
   
      frameStack.push();
      {
         
       //  frameStack.rotateY(45);
         frameStack.rotateZ(75);
          frameStack.rotateY(15);
         turret->render(frameStack.top());
		  frameStack.push();
      {
         
       //  frameStack.rotateY(65);
       frameStack.rotateZ(55);
         frameStack.rotateX(35);
		   frameStack.rotateY(25);
         ast->render(frameStack.top());
		  frameStack.push();
      {
         
         frameStack.rotateY(75);
         frameStack.rotateZ(55);
         frameStack.rotateX(25);
         roid->render(frameStack.top());
      }
	  frameStack.pop();
      }
	  frameStack.pop();
      }
      frameStack.pop();
   }
   frameStack.pop();
}
