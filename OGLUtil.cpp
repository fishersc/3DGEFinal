#include "OGLUtil.h"

glm::mat3 OGLUtil::rotateX(float degrees)
{
	float fAngRad = degToRad(degrees);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[1].y = fCos; theMat[2].y = -fSin;
	theMat[1].z = fSin; theMat[2].z = fCos;
	return theMat;
}

glm::mat3 OGLUtil::rotateY(float degrees)
{
	float fAngRad = degToRad(degrees);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[0].x = fCos;  theMat[2].x = fSin;
	theMat[0].z = -fSin; theMat[2].z = fCos;
	return theMat;
}

glm::mat3 OGLUtil::rotateZ(float degrees)
{
	float fAngRad = degToRad(degrees);
	float fCos = cosf(fAngRad);
	float fSin = sinf(fAngRad);

	glm::mat3 theMat(1.0f);
	theMat[0].x = fCos; theMat[1].x = -fSin;
	theMat[0].y = fSin; theMat[1].y = fCos;
	return theMat;
}

glm::mat4 OGLUtil::translate(float x, float y, float z)
{
   glm::mat4 theMat(1.0f);
   theMat[3].x = x;
   theMat[3].y = y;
   theMat[3].z = z;
   return theMat;
}
