#pragma once
#ifndef OGL_REVERSE_SPHERICAL_CAMERA_H
#define OGL_REVERSE_SPHERICAL_CAMERA_H

#include "oglsphericalcamera.h"

/**
   Defines a reverse spherical camera, where the camera is at a fixed position, 
   targeting a point that circles about the camera.
**/
class OGLReverseSphericalCamera :  public OGLSphericalCamera
{
public:
   // Constructor
   OGLReverseSphericalCamera(void);

   // Destructor
   virtual ~OGLReverseSphericalCamera(void);

   // Moves the camera by calculating its position and where its looking.
   // Position is given
   // The target is determined from rho, theta, and phi.
   // Look direction is a vector from target to position
   void animate();

   virtual void changeThetaPhi(float phiRatio, float thetaRatio);
};

#endif

