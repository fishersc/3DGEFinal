#include "ReferenceFrameStack.h"


ReferenceFrameStack::ReferenceFrameStack(void) 
{
}

ReferenceFrameStack::~ReferenceFrameStack(void)
{
}

ReferenceFrame ReferenceFrameStack::pop()
{
   currFrame = frames.top();
	frames.pop();
   return currFrame;
}

void ReferenceFrameStack::push()
{
   frames.push(currFrame);
}