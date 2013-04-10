#include "OGLGameObject.h"
#include "AbstractBehavior.h"

#include <glm/gtc/type_ptr.hpp>

OGLGameObject::OGLGameObject(void)
{
   shader = 0;
}

OGLGameObject::~OGLGameObject(void)
{
}

void OGLGameObject::createFromFile(std::string filename)
{
   vertexData.readFromFile(filename);
   generateVBO();
}

void OGLGameObject::setTransformMatrixUniform(GLuint unif)
{
   transformMatrixUnif = unif;
}

void OGLGameObject::setNormalTransformMatrixUniform(GLuint unif)
{
   normTransformMatrixUnif = unif;
}

void OGLGameObject::setAmbientIntensityUniform(GLuint unif)
{
   ambientIntensityUnif = unif;
}

void OGLGameObject::setSpecularUniform(GLuint unif)
{
   specularUnif = unif;
}

void OGLGameObject::setShininessUniform(GLuint unif)
{
   shininessUnif = unif;
}

void OGLGameObject::render()
{
   render(frame);
}

void OGLGameObject::update()
{
   if(behavior) behavior->updateState();
}

void OGLGameObject::animate(float durationMS)
{
   if(behavior) behavior->animate(durationMS);
}

void OGLGameObject::render(const ReferenceFrame& frame)
{
   glUseProgram(shader);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
      vertexData.getComponentCount(ObjectData::POSITION),  
		GL_FLOAT,       
		GL_FALSE,
		vertexData.getStride(ObjectData::POSITION), 
      (void*)vertexData.getStartingOffset(ObjectData::POSITION)
	); 
	// Colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		vertexData.getComponentCount(ObjectData::COLOR),
		GL_FLOAT,                  
		GL_FALSE,
		vertexData.getStride(ObjectData::COLOR), 
		(void*)vertexData.getStartingOffset(ObjectData::COLOR)
	);
   // Normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		vertexData.getComponentCount(ObjectData::NORMAL),
		GL_FLOAT,                  
		GL_FALSE,
		vertexData.getStride(ObjectData::NORMAL), 
		(void*)vertexData.getStartingOffset(ObjectData::NORMAL)
	);

   switch(vertexData.getPrimitive()){
      case ObjectData::TRIANGLES:{
         glUniformMatrix4fv(transformMatrixUnif, 1, GL_FALSE, glm::value_ptr(frame.orientation));
         glUniform4f(ambientIntensityUnif, material.getAmbient().r, material.getAmbient().g, material.getAmbient().b, material.getAmbient().a);
         glUniform4f(specularUnif, material.getSpecular().r, material.getSpecular().g, material.getSpecular().b, material.getSpecular().a);
         glUniform1f(shininessUnif, material.getShininess());
         glDrawArrays(GL_TRIANGLES, 0, vertexData.getNumberOfVertices());
         break;
      }
      case ObjectData::POINTS:
         glDrawArrays(GL_POINTS, 0, vertexData.getNumberOfVertices());
         break;
      case ObjectData::LINES:
         glUniformMatrix4fv(transformMatrixUnif, 1, GL_FALSE, glm::value_ptr(frame.orientation));
         glDrawArrays(GL_LINES, 0, vertexData.getNumberOfVertices());
         break;
   }

   glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
   glUseProgram(0);
}

void OGLGameObject::generateVBO()
{
   vboID = createHandle(GL_ARRAY_BUFFER, vertexData.getData(), vertexData.sizeInBytes());
}

GLuint OGLGameObject::createHandle(GLenum target, const void* bufferData, GLsizei bufferSize)
{
   GLuint vboID = 0;
   // Declare the buffer object and store a handle to the object
   glGenBuffers(1, &vboID);
   // Bind the object to the binding target
   glBindBuffer(target, vboID);
   // Allocate memory in the GPU for the buffer bound to the binding target and then copy the data
   glBufferData(target, bufferSize, bufferData, GL_STATIC_DRAW);
   // Good practice to cleanup by unbinding 
   glBindBuffer(target, 0);
   // Return the handle
   return vboID;
}
