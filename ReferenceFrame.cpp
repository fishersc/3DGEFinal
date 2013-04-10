#include "ReferenceFrame.h"

ReferenceFrame::ReferenceFrame(void) : orientation(1.0f)
{
}


ReferenceFrame::~ReferenceFrame(void)
{
}

void ReferenceFrame::setPosition(const glm::vec3& position)
{
   orientation[3] = glm::vec4(position, 1.0f);
}

void ReferenceFrame::scale(const glm::vec3& scaleVec)
{
	glm::mat4 scaleMat(1.0f);
	scaleMat[0].x = scaleVec.x;
	scaleMat[1].y = scaleVec.y;
	scaleMat[2].z = scaleVec.z;

	orientation = orientation * scaleMat;
}

void ReferenceFrame::translate(const glm::vec3& offset)
{
	glm::mat4 translateMat(1.0f);
	translateMat[3] = glm::vec4(offset, 1.0f);

	orientation = orientation * translateMat;
}