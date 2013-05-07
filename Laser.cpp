#include "Laser.h"


Laser::Laser(float speed) : Cuboid(glm::vec3(), .3, .3, 2)
{

	 if(speed > 0) this->speed = speed;
	totalTime = 0;
  

}

Laser::~Laser(void)
{
}

 void Laser::fire(const glm::vec3& position, const ReferenceFrame& frame)
 {
	 this->frame = frame;
	 this->frame.setPosition(position);
	 startPos = position;
 }

void Laser::animate(float durationMS)
{
	float t = durationMS/1000.0f;
	totalTime += t;
	glm::vec3 pos;
	pos.x = startPos.x + (frame.orientation[1].x * speed * totalTime);
	pos.z = startPos.z + (frame.orientation[1].z * speed * totalTime) + (0.5f * -(speed*250+80) * totalTime);
	pos.y = 2;
	frame.setPosition(pos);
} 





