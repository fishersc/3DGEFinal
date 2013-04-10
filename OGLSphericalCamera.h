#pragma once
#ifndef OGL_SPHERICAL_CAMERA_H
#define OGL_SPHERICAL_CAMERA_H

#include "abstractcamera.h"

#include <glm\glm.hpp>

/**
   Defines a Spherical camera, where the camera is circling about a target point always looking 
   at that point.
**/
class OGLSphericalCamera : public AbstractCamera
{
public:
   // The structure for the spherical coordinates
   struct Spherical{
      float rho, phi, theta;
   } cameraPosSpherical;

   glm::mat4 transformMatrix;
   glm::vec3 cameraTarget;
   glm::vec3 position;
   glm::vec3 lookDir;

protected:
   glm::vec3 up;

public:
   // Constructor
   OGLSphericalCamera(void);

   // Destructor
   virtual ~OGLSphericalCamera(void);

   // Moves the camera by calculating its position and where its looking.
   // Position is determined from rho, theta, and phi.
   // Look direction is a vector from position to the target
   virtual void animate();

   // Calculates the camera's transform matrix
   virtual void updateTransform();

   // Calculates the theta and phi of the spherical coordinates
   // Params:
   //    mouseX - on-screen mouse X position
   //    mouseY - on-screen mouse Y position
   //    windowWidth - window width (pixels)
   //    windowHeight - window height (pixels)
   void changeThetaPhi(int mouseX, int mouseY, int windowWidth, int windowHeight);
};

#endif

