#pragma once
#ifndef WINDOWS_CONSOLE_LOGGER_H
#define WINDOWS_CONSOLE_LOGGER_H

#include <string>
using std::wstring;
using std::string;

#define _LOGGING_

class WindowsConsoleLogger
{
public:
	static const int MAX_CONSOLE_LINES = 500;
public:
	WindowsConsoleLogger(void);
	~WindowsConsoleLogger(void);

	static void redirectIOToConsole();

	static void info(const wstring& tag, const wstring& message);
	static void error(const wstring& tag, const wstring& message);
	static void debug(const wstring& tag, const wstring& message);
	static void info(const string& tag, const string& message);
	static void error(const string& tag, const string& message);
	static void debug(const string& tag, const string& message);
	static void info(const char* tag, const char* message);
	static void error(const char* tag, const char* message);
	static void debug(const char* tag, const char* message);
};

typedef WindowsConsoleLogger WCLog;

#endif

