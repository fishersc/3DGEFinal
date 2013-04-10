#pragma once
#ifndef ABSTRACT_CAMERA_H
#define ABSTRACT_CAMERA_H

/**
   Specifies the Camera interface
**/
class AbstractCamera
{
public:
   // Constructor
   AbstractCamera(void);

   // Destructor
   virtual ~AbstractCamera(void);

   // Should be implemented to move the camera
   virtual void animate() = 0;

   // Should be implemented to set up the camera transform 
   virtual void updateTransform() = 0;

};

#endif
