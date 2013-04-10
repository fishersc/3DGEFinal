#include <Windows.h>
#include "WindowsConsoleLogger.h"
#include <io.h>
#include <FCNTL.H> // _O_TEXT
#include <iostream>
using namespace std;

WindowsConsoleLogger::WindowsConsoleLogger(void)
{
}

WindowsConsoleLogger::~WindowsConsoleLogger(void)
{
}

void WindowsConsoleLogger::info(const wstring& tag, const wstring& message)
{
	wcout << "INFO- (" << tag << ") " << message << endl; 
}

void WindowsConsoleLogger::error(const wstring& tag, const wstring& message)
{
	wcerr << "ERROR- (" << tag << ") " << message << "  !" << endl;
}

void WindowsConsoleLogger::debug(const wstring& tag, const wstring& message)
{
	wcerr << "DEBUG- (" << tag << ") '" << message << "'" << endl;
}

void WindowsConsoleLogger::info(const string& tag, const string& message)
{
	cout << "INFO- (" << tag << ") " << message << endl; 
}

void WindowsConsoleLogger::error(const string& tag, const string& message)
{
	cerr << "ERROR- (" << tag << ") " << message << "  !" << endl;
}

void WindowsConsoleLogger::debug(const string& tag, const string& message)
{
	cerr << "DEBUG- (" << tag << ") '" << message << "'" << endl;
}

void WindowsConsoleLogger::info(const char* tag, const char* message)
{
	cout << "INFO- (" << tag << ") " << message << endl; 
}

void WindowsConsoleLogger::error(const char* tag, const char* message)
{
	cerr << "ERROR- (" << tag << ") " << message << "  !" << endl;
}

void WindowsConsoleLogger::debug(const char* tag, const char* message)
{
	cerr << "DEBUG- (" << tag << ") '" << message << "'" << endl;
}

void WindowsConsoleLogger::redirectIOToConsole()
{
	// Source: http://dslweb.nwnexus.com/~ast/dload/guicon.htm (Dec 5, 2012)
	// Allocate a console for this app
	AllocConsole();

	// Set the screen buffer to be big enough to let us scroll text
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),	&coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// Redirect unbuffered STDOUT to the console
	long lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	FILE* fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	// Redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );

	// Redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );

	// Make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	ios::sync_with_stdio();
}