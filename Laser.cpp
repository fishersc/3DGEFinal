#include "Laser.h"
#include "AbstractBehavior.h"


Laser::Laser(const glm::vec3& pos)
{
   laser = new Cuboid(pos, .3, .3, 2);
   laser->material.setDiffuse(1, 1, 1); 
   laser->material.setAmbient(0.6f, 0.6f, 0.6f);
   laser->vertexData.setToOneColor(laser->material.getDiffuse().r, laser->material.getDiffuse().g, laser->material.getDiffuse().b);
   laser->generateVBO();

   angleY = 0;
   angleZ = 0;
   speedZ = 60;
}

Laser::~Laser(void)
{
	delete laser;
}

void Laser::update()
{
   if(laser->behavior){
      laser->behavior->updateState();
   }
}

void Laser::animate(float durationMS)
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

void Laser::setTransformMatrixUniform(GLuint unif)
{
   laser->setTransformMatrixUniform(unif);
}

void Laser::setAmbientIntensityUniform(GLuint unif)
{
   laser->setAmbientIntensityUniform(unif);
}

void  Laser::setSpecularUniform(GLuint unif)
{
   laser->setSpecularUniform(unif);
}

void  Laser::setShininessUniform(GLuint unif)
{
   laser->setShininessUniform(unif);

}

void Laser::setShader(GLuint shader)
{
   laser->setShader(shader);
}

void Laser::render()
{
   frameStack.setBaseFrame(laser->frame);
   laser->render();
}




