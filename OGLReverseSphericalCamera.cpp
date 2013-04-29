#include "OGLReverseSphericalCamera.h"
#include "OGLUtil.h"

#include <iostream>

OGLReverseSphericalCamera::OGLReverseSphericalCamera(void)
{
}


OGLReverseSphericalCamera::~OGLReverseSphericalCamera(void)
{
}

void OGLReverseSphericalCamera::changeThetaPhi(float phiRatio, float thetaRatio)
{
   cameraPosSpherical.phi = (phiRatio * 360.0f) - 90.0f;
   cameraPosSpherical.theta = (thetaRatio * 160) - 80.0f;
}

void OGLReverseSphericalCamera::animate()
{
   // See http://en.wikipedia.org/wiki/Spherical_coordinate_system#Cartesian_coordinates
   // Spherical to Cartesian
   // x = r * sin(theta) * cos(phi)
   // y = r * cos(theta)
   // z = r * sin(theta) * sin(phi)
    
   float phi = OGLUtil::degToRad(cameraPosSpherical.phi);
   float theta = OGLUtil::degToRad(cameraPosSpherical.theta + 90.0f); // Remember -90 to 90
    
   float fSinTheta = sinf(theta);
   float fCosTheta = cosf(theta);
   float fCosPhi = cosf(phi);
   float fSinPhi = sinf(phi);
    
   glm::vec3 dirToTarget(fSinTheta * fCosPhi, -fCosTheta, fSinTheta * fSinPhi);
   cameraTarget = (dirToTarget * cameraPosSpherical.rho) + position;

   lookDir = glm::normalize(position - cameraTarget);
}

