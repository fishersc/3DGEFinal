#pragma comment(lib, "winmm.lib")

#include "WindowsTimer.h"
#include <time.h>

#include <iostream>

WindowsTimer::WindowsTimer(void)
{
   // CLOCKS_PER_SEC documentation: http://msdn.microsoft.com/en-us/library/8001551c%28v=vs.100%29.aspx (Feb 2, 2013)
   // ---------------------------------------------------------------------------------------------------------------

   start.QuadPart = 0L;
   finish.QuadPart = 0L;
   duration = 0.0f;
   ticksPerSecond.QuadPart = CLOCKS_PER_SEC;
   highResolutionFlag = false;
   initialize();
}

WindowsTimer::~WindowsTimer(void)
{
}

void WindowsTimer::initialize()
{
   if (!QueryPerformanceFrequency(&ticksPerSecond)){
      // System doesn't support hi-res timer
      highResolutionFlag = false;
      ticksPerSecond.QuadPart = CLOCKS_PER_SEC;
   }
   else{
      highResolutionFlag = true;
   }

   if(highResolutionFlag){
      std::cout << "Using High-res timer" << " ";
   }
   else{
      std::cout << "Using Low-res timer" << " ";
   }

}

void WindowsTimer::startTiming()
{
   getCurrentTime(start);
   duration = 0.0f;
}


void WindowsTimer::stop()
{
   getCurrentTime(finish);
   duration = (float)(finish.QuadPart - start.QuadPart);
   getCurrentTime(start);
}

float WindowsTimer::getElapsedTimeInSeconds()
{
   static LARGE_INTEGER s_lastTime = start;
   LARGE_INTEGER currentTime;

   getCurrentTime(currentTime);
   float seconds = 
      ((float)(currentTime.QuadPart - s_lastTime.QuadPart)) / (float)ticksPerSecond.QuadPart;

   s_lastTime = currentTime;
   return seconds;
}

float WindowsTimer::getCurrentTimeInSeconds()
{
   LARGE_INTEGER currentTime;
   getCurrentTime(currentTime);
   float seconds = ((float)(currentTime.QuadPart)) / (float)ticksPerSecond.QuadPart;
   return seconds;
}

float WindowsTimer::getCurrentTimeInMilliseconds()
{
   LARGE_INTEGER currentTime;
   getCurrentTime(currentTime);
   float ms = (((float)(currentTime.QuadPart)) / (float)ticksPerSecond.QuadPart) * 1000;
   return ms;
}

float WindowsTimer::getFPS(unsigned long elapsedFrames)
{
   static LARGE_INTEGER s_lastTime = start;
   LARGE_INTEGER currentTime;

   getCurrentTime(currentTime);
   float fps = 
      ((float)(elapsedFrames * ticksPerSecond.QuadPart)) / 
         ((float)currentTime.QuadPart - (float)s_lastTime.QuadPart);

   s_lastTime = currentTime;
   return fps;
}

float WindowsTimer::lockFPS(unsigned long targetFPS)
{
   if( targetFPS == 0 ) targetFPS = 1;

   static LARGE_INTEGER s_lastTime = start;
   LARGE_INTEGER currentTime;
   float fps;

   do{
      getCurrentTime(currentTime);
      fps = 
         ((float)ticksPerSecond.QuadPart) / 
            ((float)(currentTime.QuadPart - s_lastTime.QuadPart));
   }while( fps > (float)targetFPS);

   s_lastTime = currentTime;
   return fps;
}

void WindowsTimer::getCurrentTime(LARGE_INTEGER& currentTime)
{
   if(highResolutionFlag){
      QueryPerformanceCounter(&currentTime);
   }
   else{
      currentTime.QuadPart = timeGetTime();
   }
}