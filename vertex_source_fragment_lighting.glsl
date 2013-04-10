#version 130

precision highp float;

in vec4 position;
in vec4 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;
out vec4 fragGlobalColor;
out vec3 fragNormal;
out vec3 fragPosition;
out vec3 fragLightPosition;
out vec3 fragGlobalLightPosition;
out vec3 fragCameraPosition;

uniform vec3 worldGlobalLightPos;
uniform vec4 globalLightIntensity;
uniform vec3 worldCameraPos;
uniform vec4 worldLightPos;
uniform mat4 cameraToClipMatrix;
uniform mat4 worldToCameraMatrix;
uniform mat4 localToWorldMatrix;
 
void main()
{
	vec4 positionWorldSpace = localToWorldMatrix * position;
	gl_Position = cameraToClipMatrix * worldToCameraMatrix * positionWorldSpace;

	fragNormal = mat3(localToWorldMatrix) * vertexNormal;
	vec3 unitNormal = normalize(fragNormal);
	vec3 toLightDir = normalize(worldGlobalLightPos);
	float cosAngIncidence = dot(unitNormal, toLightDir);
	cosAngIncidence = clamp(cosAngIncidence, 0.0, 1.0);

	fragLightPosition = vec3(worldLightPos);
	fragColor = vertexColor;
	fragGlobalColor = vertexColor * globalLightIntensity * cosAngIncidence;
	fragPosition = vec3(positionWorldSpace);
	fragGlobalLightPosition = worldGlobalLightPos;
	fragCameraPosition = worldCameraPos;
}
