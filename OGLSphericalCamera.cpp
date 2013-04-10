#include "OGLSphericalCamera.h"
#include "OGLUtil.h"

OGLSphericalCamera::OGLSphericalCamera(void)
{
   up = glm::vec3(0.0f, 1.0f, 0.0f);
}


OGLSphericalCamera::~OGLSphericalCamera(void)
{
}

void OGLSphericalCamera::changeThetaPhi(int mouseX, int mouseY, int windowWidth, int windowHeight)
{
   // Putting the mouse pointer at the center of the screen will point down the Z-axis
   cameraPosSpherical.phi = ((mouseX / (float)windowWidth) * 360 - 180) + 90;
   cameraPosSpherical.theta = (mouseY / (float)windowHeight) * 160 - 80;
}

void OGLSphericalCamera::animate()
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
    
   glm::vec3 dirToCamera(fSinTheta * fCosPhi, fCosTheta, fSinTheta * fSinPhi);
   position = (dirToCamera * cameraPosSpherical.rho) + cameraTarget;

   lookDir = glm::normalize(cameraTarget - position);
}

void OGLSphericalCamera::updateTransform()
{
	glm::vec3 upDir = glm::normalize(up);

	glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
	glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

	glm::mat4 rotMat(1.0f);
	rotMat[0] = glm::vec4(rightDir, 0.0f);
	rotMat[1] = glm::vec4(perpUpDir, 0.0f);
	rotMat[2] = glm::vec4(-lookDir, 0.0f); // Negate the look direction to point at the look point

   // Since we are building a world-to-camera matrix, we invert the matrix.
   // Transposing a rotation matrix inverts it!
	rotMat = glm::transpose(rotMat);

   // Translate the camera to the origin
	glm::mat4 transMat(1.0f);
	transMat[3] = glm::vec4(-position, 1.0f);

   // Translate and then rotate
	transformMatrix = rotMat * transMat;
}
