#include "Material.h"


Material::Material(void)
{
   setDiffuse(0.5f, 0.5f, 0.5f);
   setAmbient(0.2f, 0.2f, 0.2f);
   setSpecular(0.0f, 0.0f, 0.0f);
   shininess = 0;
}


Material::~Material(void)
{
}

void Material::setDiffuse(float r, float g, float b, float a)
{
   if(r >= 0 && r <= 1) diffuse.r = r;
   if(g >= 0 && g <= 1) diffuse.g = g;
   if(b >= 0 && b <= 1) diffuse.b = b;
   if(a >= 0 && a <= 1) diffuse.a = a;
}

void Material::setAmbient(float r, float g, float b, float a)
{
   if(r >= 0 && r <= 1) ambient.r = r;
   if(g >= 0 && g <= 1) ambient.g = g;
   if(b >= 0 && b <= 1) ambient.b = b;
   if(a >= 0 && a <= 1) ambient.a = a;
}

void Material::setSpecular(float r, float g, float b, float a)
{
   if(r >= 0 && r <= 1) specular.r = r;
   if(g >= 0 && g <= 1) specular.g = g;
   if(b >= 0 && b <= 1) specular.b = b;
   if(a >= 0 && a <= 1) specular.a = a;
}

void Material::setShininess(float shininess)
{
   if(shininess >= 0) this->shininess = shininess;
}

