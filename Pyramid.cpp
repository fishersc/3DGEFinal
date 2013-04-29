#include "Pyramid.h"
#include "OGLUtil.h"

Pyramid::Pyramid(void)
{
   createFromFile("pyramid.odat");
   angleZ = 0;
}


Pyramid::~Pyramid(void)
{
}

void Pyramid::animate(float durationMS)
{
   angleZ = angleZ + (90 * (durationMS/1000.0f)); // 90 degrees per second
   if(angleZ > 360) angleZ -= 360;

   float sinRad = sinf(OGLUtil::degToRad(angleZ));
   float cosRad = cosf(OGLUtil::degToRad(angleZ));
   frame.orientation[0].x = cosRad;
   frame.orientation[0].y = sinRad;
   frame.orientation[1].x = -sinRad;
   frame.orientation[1].y = cosRad;
}

