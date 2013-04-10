#pragma once
#ifndef REFERENCE_FRAME_STACK_H
#define REFERENCE_FRAME_STACK_H

#include <stack>
#include <glm/glm.hpp>
#include "ReferenceFrame.h"

/**
   Manages a stack of reference frames
**/
class ReferenceFrameStack
{
private:
   // The current frame i.e. typically the top of the stack
   ReferenceFrame currFrame;
   // The stack of frames
	std::stack<ReferenceFrame> frames;

public:
   // Constructor
   ReferenceFrameStack(void);
   // Destructor
   ~ReferenceFrameStack(void);

   // Sets the base frame to the stack i.e. the top
   // Param:
   //    frame - the frame
   inline void setBaseFrame(ReferenceFrame frame) 
   {
      currFrame = frame;
   }

   // Returns the top of the stack i.e. the current frame
   inline ReferenceFrame top() { return currFrame; }

   // Rotates the top frame about the x axis
   inline void rotateX(float degrees) { currFrame.rotateX(degrees); }

   // Rotates the top frame about the y axis
   inline void rotateY(float degrees) { currFrame.rotateY(degrees); }

   // Rotates the top frame about the z axis
   inline void rotateZ(float degrees) { currFrame.rotateZ(degrees); }

   // Translates the top frame by x, y, z
   inline void translate(float x, float y, float z) { currFrame.translate(x, y, z); }

   // Pops the top of the stack
   ReferenceFrame pop();

   // Pushes the current frame to the stack
   void push();
};

#endif