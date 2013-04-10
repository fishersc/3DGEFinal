#pragma once
#ifndef OGL_SHADER_MANAGER_H
#define OGL_SHADER_MANAGER_H

#include <string>
using std::string;

#include <GL\glew.h>

#include <map>
using std::map;

/**
  Used to manage the OGL shaders
*/
class OGLShaderManager
{
public:

   struct ShaderData{
      // Handle to the shader program
	   GLuint shaderProgram;
      // Handles to the vertex and fragment shaders
	   GLuint vertexShader, fragmentShader;
      // The names of the shader program files
	   string vertexShaderFilename, fragmentShaderFilename;
      // These are the uniforms associated with each shader
      map<string, GLuint> unifs;
   };

   map<string, ShaderData> shaders;

public:
   // Constructor
	OGLShaderManager();

   // Destructor
	~OGLShaderManager(void);

   // Compiles the shader program
   // Params
   //    which - the name of shader to compile
	void compileShaderProgram(const string& which);

   // Links the shader program
   // Params
   //    which - the name of shader to link
	void linkShaderProgram(const string& which);

   // Returns the handle to the shader program.  If it returns zero then there is no
   // shader program.
	GLuint getShaderProgram(const string& which)  { return shaders[which].shaderProgram; }

   // Returns the handle to the fragment shader.  If it returns zero then there is no 
   // shader program.
	GLuint getFragmentShader(const string& which)  { return shaders[which].fragmentShader; }

   // Adds a shader to the manager
   // Params:
   //    name - the name used to retreive the shader
   //    vertexShaderFilename - the name of the vertex shader program file
   //    fragmentShaderFilename - the name of the fragment shader program file
	void addShader(string name, string vertexShaderFilename, string fragmentShaderFilename);

private:
   // Compiles a shader
   // Params:
   //    type - the target type E.g. GL_BUFFER_ARRAY
   //    source - c-string of the program
   // Returns:
   //    The handle to the shader program.  Zero is returned if the shader could
   //    not compile.
	GLuint makeShader(GLenum type, const GLchar* source);
   // Links the shaders into a shader program
   // Params:
   //    vertexShader - handle to the vertex shader
   //    fragmentShader - handle to the fragment shader
   // Returns:
   //    The handle to the linked shader program.  Zero is returned if the shader program was
   //    not compiled
	GLuint linkShader(GLuint vertexShader, GLuint fragmentShader);
   // Used to show any shader compilation or linking errors
	void showInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
};

#endif

