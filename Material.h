#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
public:
   struct Color { float r, g, b, a; };

protected:
   Color diffuse;
   Color ambient;
   Color specular;
   float shininess;

public:
   Material(void);
   virtual ~Material(void);

   void setDiffuse(float r, float g, float b, float a=1.0f);
   void setAmbient(float r, float g, float b, float a=1.0f);
   void setSpecular(float r, float g, float b, float a=1.0f);
   void setShininess(float shininess);

   inline const Color& getDiffuse() const { return diffuse; }
   inline const Color& getAmbient() const { return ambient; }
   inline const Color& getSpecular() const { return specular; }
   inline float getShininess() const { return shininess; }

};

#endif

