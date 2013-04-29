#include "AbstractGameObject.h"
#include "AbstractBehavior.h"

AbstractGameObject::AbstractGameObject(void)
{
   frame.orientation[0].x = 1.0f;
   frame.orientation[1].y = 1.0f;
   frame.orientation[2].z = 1.0f;
   frame.orientation[3].w = 1.0f;
   behavior = NULL;
   useBoundingBox = false;
   speed = 5;
}

AbstractGameObject::AbstractGameObject(const AbstractGameObject& copy)
{
   vertexData = copy.vertexData;
   behavior = NULL;
   material = copy.material;
   frame = copy.frame;
   localPosition = copy.localPosition;
}

AbstractGameObject::~AbstractGameObject(void)
{
   if(behavior) delete behavior;
}
