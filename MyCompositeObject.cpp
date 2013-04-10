#include "MyCompositeObject.h"
#include "AbstractBehavior.h"

MyCompositeObject::MyCompositeObject(const glm::vec3& pos)
{
   base = new Cuboid(pos, 2, 2, 2);
   base->material.setDiffuse(1, 0, 1); 
   base->material.setAmbient(0.6f, 0.6f, 0.6f);
   base->vertexData.setToOneColor(base->material.getDiffuse().r, base->material.getDiffuse().g, base->material.getDiffuse().b);
   base->generateVBO();

   torso = new Cuboid(glm::vec3(0, 0, 0), 1, 1, 1);
   torso->material.setDiffuse(1, 0, 1); 
   torso->material.setAmbient(0.6f, 0.6f, 0.6f);
   torso->vertexData.setToOneColor(torso->material.getDiffuse().r, torso->material.getDiffuse().g, torso->material.getDiffuse().b);
   torso->generateVBO();

   turret = new Cuboid(glm::vec3(0, 0, 0), 1.5, 0.5, 0.5);
   turret->material.setDiffuse(1, 1, 1); 
   turret->material.setAmbient(0.6f, 0.6f, 0.6f);
   turret->vertexData.setToOneColor(turret->material.getDiffuse().r, turret->material.getDiffuse().g, turret->material.getDiffuse().b);
   turret->generateVBO();

   angleY = 0;
   angleZ = 0;
   speedZ = 60;
}


MyCompositeObject::~MyCompositeObject(void)
{
   delete base;
   delete torso;
   delete turret;
}

void MyCompositeObject::update()
{
   if(base->behavior){
      base->behavior->updateState();
   }
}

void MyCompositeObject::animate(float durationMS)
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

   
   if(base->behavior){
      base->behavior->animate(durationMS);
   }
} 

void MyCompositeObject::setTransformMatrixUniform(GLuint unif)
{
   base->setTransformMatrixUniform(unif);
   torso->setTransformMatrixUniform(unif);
   turret->setTransformMatrixUniform(unif);
}

void MyCompositeObject::setAmbientIntensityUniform(GLuint unif)
{
   base->setAmbientIntensityUniform(unif);
   torso->setAmbientIntensityUniform(unif);
   turret->setAmbientIntensityUniform(unif);
}

void  MyCompositeObject::setSpecularUniform(GLuint unif)
{
   base->setSpecularUniform(unif);
   torso->setSpecularUniform(unif);
   turret->setSpecularUniform(unif);
}

void  MyCompositeObject::setShininessUniform(GLuint unif)
{
   base->setShininessUniform(unif);
   torso->setShininessUniform(unif);
   turret->setShininessUniform(unif);
}

void MyCompositeObject::setShader(GLuint shader)
{
   base->setShader(shader);
   torso->setShader(shader);
   turret->setShader(shader);
}

void MyCompositeObject::render()
{
   frameStack.setBaseFrame(base->frame);
   base->render();
   frameStack.push();
   {
      frameStack.translate(0, 1.5f, 0);
      frameStack.rotateY(angleY);
      torso->render(frameStack.top());
   
      frameStack.push();
      {
         frameStack.translate(0, 0, 0.75f);
         frameStack.rotateY(90);
         frameStack.rotateZ(angleZ);
         frameStack.translate(-0.4f, 0, 0);
         turret->render(frameStack.top());
      }
      frameStack.pop();
   }
   frameStack.pop();
}
