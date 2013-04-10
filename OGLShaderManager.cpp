#include "OGLShaderManager.h"
#include "TextFileReader.h"
#include "WindowsConsoleLogger.h"

#include <iostream>
using std::cout;
using std:: endl;

OGLShaderManager::OGLShaderManager()
{
}

void OGLShaderManager::addShader(string name, string vertexShaderFilename, string fragmentShaderFilename)
{
   ShaderData data;
	data.vertexShaderFilename = vertexShaderFilename;
	data.fragmentShaderFilename = fragmentShaderFilename;
   shaders[name] = data;
}

OGLShaderManager::~OGLShaderManager(void)
{
}

void OGLShaderManager::compileShaderProgram(const string& which)
{
	TextFileReader vReader(shaders[which].vertexShaderFilename);
	string contents = vReader.readContents();
	GLchar* vertexSource = (GLchar*)contents.c_str();
	shaders[which].vertexShader = makeShader(GL_VERTEX_SHADER, vertexSource);
	if(shaders[which].vertexShader == 0) return;

	TextFileReader fReader(shaders[which].fragmentShaderFilename);
	contents = fReader.readContents();
	GLchar* fragmentSource = (GLchar*)contents.c_str();
	shaders[which].fragmentShader = makeShader(GL_FRAGMENT_SHADER, fragmentSource);
	if(shaders[which].fragmentShader == 0) return;
}

void OGLShaderManager::linkShaderProgram(const string& which)
{
	if(shaders[which].vertexShader == 0 || shaders[which].fragmentShader == 0){
		WCLog::error("lineShaderProgram", "Failed to link the shader"); 
		return;
	}

	shaders[which].shaderProgram = linkShader(shaders[which].vertexShader, shaders[which].fragmentShader);
	glDeleteShader(shaders[which].vertexShader);
	glDeleteShader(shaders[which].fragmentShader);
	shaders[which].vertexShader = 0;
	shaders[which].fragmentShader = 0;
}

GLuint OGLShaderManager::makeShader(GLenum type, const GLchar* source)
{
	GLint length = sizeof(GLchar) * strlen(source);
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar**)&source, &length);
	glCompileShader(shader);
	GLint shaderOk = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderOk);
	if(!shaderOk){
		WCLog::error("makeShader", "Failed to compile the shader");
		showInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}

void OGLShaderManager::showInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
	GLint logLength;
    glGet__iv(object, GL_INFO_LOG_LENGTH, &logLength);
    char* log = (char*)malloc(logLength);
    glGet__InfoLog(object, logLength, NULL, log);
	WCLog::error("Info Log", log);
    free(log);
}

GLuint OGLShaderManager::linkShader(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	GLint programOk = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &programOk);
	if(!programOk){
		WCLog::error("linkShader", "Failed to link the shader");
		showInfoLog(program, glGetProgramiv, glGetProgramInfoLog);
		glDeleteShader(program);
		program = 0;
	}
	return program;
}
