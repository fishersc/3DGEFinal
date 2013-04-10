#version 130

precision highp float;

in vec4 fragColor;
in vec4 fragGlobalColor;
in vec3 fragNormal;
in vec3 fragPosition;
in vec3 fragLightPosition;
in vec3 fragGlobalLightPosition;
in vec3 fragCameraPosition;

out vec4 color;

uniform vec4 lightIntensity;
uniform vec4 fragAmbientIntensity;
uniform vec4 fragSpecular;
uniform float fragShininess;

void main()
{
	vec3 unitNormal = normalize(fragNormal);
	vec3 toLightDir = normalize(fragLightPosition - fragPosition);
	vec3 toGlobalLightDir = normalize(fragGlobalLightPosition - fragPosition);

	vec3 toCameraDir = normalize(fragCameraPosition - fragPosition);
	vec3 reflectDir = reflect(-toLightDir, unitNormal);
	vec3 globalReflectDir = reflect(-toGlobalLightDir, unitNormal);
	float phongTerm = dot(toCameraDir, reflectDir);
	float globalPhongTerm = dot(toCameraDir, globalReflectDir);

	float cosAngIncidence = dot(unitNormal, toLightDir);
	cosAngIncidence = clamp(cosAngIncidence, 0.0, 1.0);

	phongTerm = clamp(phongTerm, 0.0, 1.0);
	phongTerm = cosAngIncidence != 0.0 ? phongTerm : 0.0;
	phongTerm = pow(phongTerm, fragShininess);

	float globalCosAngIncidence = dot(unitNormal, toGlobalLightDir);
	globalCosAngIncidence = clamp(globalCosAngIncidence, 0.0, 1.0);

	globalPhongTerm = clamp(globalPhongTerm, 0.0, 1.0);
	globalPhongTerm = globalCosAngIncidence != 0.0 ? globalPhongTerm : 0.0;
	globalPhongTerm = pow(globalPhongTerm, fragShininess);

	color = (fragColor * lightIntensity * cosAngIncidence) + fragGlobalColor + (fragSpecular * globalPhongTerm) + (fragSpecular * phongTerm) + (fragColor * fragAmbientIntensity);
}
