#include "Astroid.h"
#include "AbstractBehavior.h"


Astroid::Astroid(const glm::vec3& pos,int size)
{
   base = new Cuboid(pos, size,size,size);
   base->material.setDiffuse(1, 1, 1); 
   base->material.setAmbient(224, 223, 219);
   base->material.setShininess(1.0);
   base->vertexData.setToOneColor(base->material.getDiffuse().r, base->material.getDiffuse().g, base->material.getDiffuse().b);
   base->generateVBO();

   ast = new Cuboid(pos, size, size,size);
   ast->material.setDiffuse(1, 1, 1); 
   ast->material.setAmbient(224, 223, 219);
   ast->material.setShininess(1.0);
   ast->vertexData.setToOneColor(base->material.getDiffuse().r, base->material.getDiffuse().g, base->material.getDiffuse().b);
   ast->generateVBO();

    roid = new Cuboid(pos, size, size, size);
   roid->material.setDiffuse(1, 1, 1); 
    roid->material.setAmbient(224, 223, 219);
	roid->material.setShininess(1.0);
	roid->vertexData.setToOneColor(base->material.getDiffuse().r, base->material.getDiffuse().g, base->material.getDiffuse().b);
   roid->generateVBO();

   torso = new Cuboid(glm::vec3(0, 0, 0), size, size, size);
   torso->material.setDiffuse(1, 1, 1); 
   torso->material.setAmbient(224, 223, 219);
   torso->material.setShininess(1.0);
   torso->vertexData.setToOneColor(torso->material.getDiffuse().r, torso->material.getDiffuse().g, torso->material.getDiffuse().b);
   torso->generateVBO();

   turret = new Cuboid(glm::vec3(0, 0, 0),size, size, size);
   turret->material.setDiffuse(1, 1, 1); 
   turret->material.setAmbient(224, 223, 219);
   turret->material.setShininess(1.0);
   turret->vertexData.setToOneColor(turret->material.getDiffuse().r, turret->material.getDiffuse().g, turret->material.getDiffuse().b);
   turret->generateVBO();

   angleY = 0;
   angleZ = 0;
   speedZ = 60;
   rotation = rand() % 70+30;
    rotation2 = rand() % 70+30;
	this->size = size;
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
   */
  
   if(base->behavior){
      base->behavior->animate(durationMS);
   }
   
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
      
      frameStack.rotateY(rotation);
	   frameStack.rotateX(rotation2);
      torso->render(frameStack.top());
   
      frameStack.push();
      {
         
       
         frameStack.rotateZ(75);
          frameStack.rotateY(rotation);
         turret->render(frameStack.top());
		  frameStack.push();
      {
         
      
       frameStack.rotateZ(55);
         frameStack.rotateX(rotation2);
		   frameStack.rotateY(rotation);
         ast->render(frameStack.top());
		  frameStack.push();
      {
         
         frameStack.rotateY(rotation);
         frameStack.rotateZ(55);
         frameStack.rotateX(rotation2);
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

BoundZ Astroid::checkSector()
{
	int sector;


	BoundZ bound;
	if(base->frame.getPosition().z <= 1000 && base->frame.getPosition().z >= 500)
	{
		sector = 0;
	}
	else if(base->frame.getPosition().z < 500 && base->frame.getPosition().z >= 0)
	{
		sector = 1;
	}
	else if(base->frame.getPosition().z < 0 && base->frame.getPosition().z >= -500)
	{
		sector = 2;
	}
	else if(base->frame.getPosition().z < -500 && base->frame.getPosition().z >= -1000)
	{
		sector = 3;
	}

	 switch(sector)
	{
		case 0:
			bound.maxZ = 500;
			bound.minZ = 1000;
			break;
		case 1:
			bound.maxZ = 0;
			bound.minZ = 500;
			break;
		case 2:
			bound.maxZ = -500;
			bound.minZ = 0;
			break;
		case 3:
			bound.maxZ = -1000;
			bound.minZ = -500;
			break;
   }

	 return bound;
}