#include "OGLGameWorld.h"
#include "Sphere.h"
#include "MyCompositeObject.h"
#include "FlatSurface.h"
#include "OGLGameEngine.h"
#include "OGLSphericalCamera.h"
#include "BackForthBehavior.h"
#include "Material.h"

#include <glm/gtc/type_ptr.hpp>
#include <glutil/glutil.h>

OGLGameWorld::OGLGameWorld(OGLGameEngine* gameEngine) : AbstractGameWorld((GameEngine*)gameEngine)
{
   zNear = 1.0f; 
	zFar = 45.0f;
   lightSpeed = 5;
}


OGLGameWorld::~OGLGameWorld(void)
{
}

void OGLGameWorld::initialize()
{
   glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

   lightDirection = glm::vec4(0.0f, 5.5f, 14.0f, 0.0f);

   light.position = glm::vec4(0, 2.5f, 0, 1);
   light.intensity = glm::vec4(0.8f, 0.8f, 0.8f, 1);

   // 0
   Sphere* ps = new Sphere(glm::vec3(light.position), 0.1f);
   ps->vertexData.setToOneColor(1, 1, 1);
   ps->generateVBO();
   objects.push_back(ps);

   // 1
   MyCompositeObject* m = new MyCompositeObject(glm::vec3(0, 1, -5));
   objects.push_back(m);

   BackForthBehavior* behave = new BackForthBehavior();
   behave->backPoint = glm::vec3(-9, 1, -5);
   behave->forthPoint = glm::vec3(9, 1, -5);
   m->base->behavior = behave;
   behave->object = m->base;

   FlatSurface* f = new FlatSurface(20, 20, 5, 5);
   f->material.setDiffuse(0.5f, 0.5f, 0.5f); 
   f->material.setAmbient(0.2f, 0.2f, 0.2f);
   f->vertexData.setToOneColor(f->material.getDiffuse().r, f->material.getDiffuse().g, f->material.getDiffuse().b);
   f->generateVBO();
   objects.push_back(f);

   Sphere* s = new Sphere(glm::vec3(0, 1.0f, 0));
   s->material.setDiffuse(0, 0, 1); 
   s->material.setAmbient(0.2f, 0.2f, 0.2f);
   s->vertexData.setToOneColor(s->material.getDiffuse().r, s->material.getDiffuse().g, s->material.getDiffuse().b);
   s->generateVBO();
   objects.push_back(s);

   Cuboid* c = new Cuboid(glm::vec3(4, 0.5f, 0));
   c->material.setDiffuse(1, 1, 0); 
   c->material.setAmbient(0.15f, 0.15f, 0);
   c->vertexData.setToOneColor(c->material.getDiffuse().r, c->material.getDiffuse().g, c->material.getDiffuse().b);
   c->generateVBO();
   objects.push_back(c);

   Cuboid* c2 = new Cuboid(glm::vec3(-4, 0.5f, 0), 2, 1, 2);
   c2->material.setDiffuse(0.5f, 1, 0.5f); 
   c2->material.setAmbient(0.15f, 0.15f, 0.15f);
   c2->vertexData.setToOneColor(c2->material.getDiffuse().r, c2->material.getDiffuse().g, c2->material.getDiffuse().b);
   c2->generateVBO();
   objects.push_back(c2);

   Sphere* s1 = new Sphere(glm::vec3(0, 1.5f, 5), 1.5);
   s1->material.setDiffuse(0.5f, 0.3f, 0.2f); 
   s1->material.setAmbient(0.5f, 0.5f, 0.5f);
   s1->material.setSpecular(0.4f, 0.4f, 0.4f);
   s1->material.setShininess(10);
   s1->vertexData.setToOneColor(s1->material.getDiffuse().r, s1->material.getDiffuse().g, s1->material.getDiffuse().b);
   s1->generateVBO();
   objects.push_back(s1);

   behave = new BackForthBehavior();
   behave->speed = 2;
   behave->backPoint = glm::vec3(0, 1.5f, 5);
   behave->forthPoint = glm::vec3(5, 5.5f, 5);
   s1->behavior = behave;
   behave->object = s1;

   OGLGameObject* object = NULL;
   shaderMan.addShader("no light", "vertex_source_no_light.glsl", "fragment_source_simple.glsl");
	shaderMan.compileShaderProgram("no light");
   glBindAttribLocation(shaderMan.shaders["no light"].fragmentShader, 0, "position");
   glBindAttribLocation(shaderMan.shaders["no light"].fragmentShader, 1, "vertexColor");
   glBindAttribLocation(shaderMan.shaders["no light"].fragmentShader, 2, "vertexNormal");
	shaderMan.linkShaderProgram("no light");
   object = (OGLGameObject*)objects[0];
   object->setShader(shaderMan.shaders["no light"].shaderProgram);
     
   shaderMan.addShader("world lighting", "vertex_source_fragment_lighting.glsl", "fragment_source_fragment_lighting.glsl");
	shaderMan.compileShaderProgram("world lighting");
	glBindAttribLocation(shaderMan.shaders["world lighting"].fragmentShader, 0, "position");
	glBindAttribLocation(shaderMan.shaders["world lighting"].fragmentShader, 1, "vertexColor");
   glBindAttribLocation(shaderMan.shaders["world lighting"].fragmentShader, 2, "vertexNormal");
	shaderMan.linkShaderProgram("world lighting");
   for(int i = 1; i < (int)objects.size(); i++){
      object = (OGLGameObject*)objects[i];
      object->setShader(shaderMan.shaders["world lighting"].shaderProgram);
   }

   GLuint shader = shaderMan.shaders["no light"].shaderProgram;
   shaderMan.shaders["no light"].unifs["cameraToClipMatrix"] = glGetUniformLocation(shader, "cameraToClipMatrix");
   shaderMan.shaders["no light"].unifs["worldToCameraMatrix"] = glGetUniformLocation(shader, "worldToCameraMatrix");
   shaderMan.shaders["no light"].unifs["localToWorldMatrix"] = glGetUniformLocation(shader, "localToWorldMatrix");
   object = (OGLGameObject*)objects[0];
   object->setTransformMatrixUniform(shaderMan.shaders["no light"].unifs["localToWorldMatrix"]);

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
   for(int i = 1; i < (int)objects.size(); i++){
      object = (OGLGameObject*)objects[i];
      object->setTransformMatrixUniform(shaderMan.shaders["world lighting"].unifs["localToWorldMatrix"]);
      object->setAmbientIntensityUniform(shaderMan.shaders["world lighting"].unifs["fragAmbientIntensity"]);
      object->setSpecularUniform(shaderMan.shaders["world lighting"].unifs["fragSpecular"]);
      object->setShininessUniform(shaderMan.shaders["world lighting"].unifs["fragShininess"]);
   }

   // Turn on the lights
   glUseProgram(shaderMan.shaders["world lighting"].shaderProgram);
   glUniform4fv(shaderMan.shaders["world lighting"].unifs["lightIntensity"], 1, glm::value_ptr(light.intensity));
   glUniform4f(shaderMan.shaders["world lighting"].unifs["globalLightIntensity"], 0.4f, 0.4f, 0.4f, 1.0f);
   glUniform3fv(shaderMan.shaders["world lighting"].unifs["worldGlobalLightPos"], 1, glm::value_ptr(lightDirection));
   glUseProgram(0);


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
   std::vector<AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      (*io)->update();
   }
}

void OGLGameWorld::animate(float durationMS)
{
   light.position.x += (lightSpeed * durationMS/1000);
   if(light.position.x >= 7) lightSpeed = -5;
   else if(light.position.x <= -7) lightSpeed = 5;
   objects[0]->frame.setPosition(glm::vec3(light.position));

	glUseProgram(shaderMan.shaders["world lighting"].shaderProgram);
   glUniform4fv(shaderMan.shaders["world lighting"].unifs["worldLightPos"], 1, glm::value_ptr(light.position));
	glUseProgram(0);

   std::vector<AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      (*io)->animate(durationMS);
   }
}

void OGLGameWorld::render()
{
   std::vector<AbstractGameObject*>::iterator io;
   for(io = objects.begin(); io != objects.end(); io++){
      (*io)->render();
   }
}

void OGLGameWorld::updateCamera()
{
   OGLSphericalCamera* camera = (OGLSphericalCamera*)gameEngine->camera;

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

void OGLGameWorld::updateViewport(float aspectRatio)
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
