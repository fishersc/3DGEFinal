#pragma once
#ifndef ABSTRACT_WINDOW_H
#define ABSTRACT_WINDOW_H

#include <string>
using std::wstring;

/**
  Encapsulates the essential operations of a UI window.  This is an abstract class.
*/
class AbstractWindow
{
public:
   /**
     The constructor
   */
	AbstractWindow(void);
   /**
     The destructor
   */
	virtual ~AbstractWindow(void);

   /**
     This interface should be used to create the window
   */
	virtual bool create() = 0;
   /**
     This interface should be used to show the window
   */
	virtual void show() = 0;
   /**
     This interface should be used to initialize the view environment
   */
	virtual void initializeEnvironment() = 0;
   /**
     This interface should be used to process the events generated for this window
   */
	virtual void processEvents() = 0;
};

#endif
