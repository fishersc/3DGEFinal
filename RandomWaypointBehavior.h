#pragma once
#ifndef RANDOM_WAYPOINT_BEHAVIOR_H
#define RANDOM_WAYPOINT_BEHAVIOR_H

#include "abstractbehavior.h"
#include <glm\glm.hpp>

class RandomWaypointBehavior : public AbstractBehavior
{
protected:
   glm::vec3 wayPoint;
   float minX, maxX, minZ, maxZ, y;

public:
   RandomWaypointBehavior(float minX, float maxX, float minZ, float maxZ, float y);
   virtual ~RandomWaypointBehavior(void);

   void generateWaypoint();

   void updateState();
   void animate(float elapsedMS);
};

#endif

