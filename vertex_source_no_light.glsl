#version 130

precision highp float;

in vec4 position;
in vec4 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

uniform mat4 cameraToClipMatrix;
uniform mat4 worldToCameraMatrix;
uniform mat4 localToWorldMatrix;
 
void main()
{
	gl_Position = cameraToClipMatrix * worldToCameraMatrix * localToWorldMatrix * position;
	fragColor = vertexColor;
}
