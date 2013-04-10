#pragma once
#ifndef TEXT_FILE_READER_H
#define TEXT_FILE_READER_H

#include <string>
using std::string;
#include <vector>
using std::vector;

/**
  Used to store the float array data
*/
struct FloatArrayData
{
   // Pointer to the data
	float* arr;
   // The number of elements in the data
	int count;
};

/**
  Has the responsibility of reading data from a text file
*/
class TextFileReader
{
private:
   // The file's name
	string filename;
   // The file's content as a string
	string contents;
   // The file's content as a collection of floats
	vector<float> values;

public:
   // Constructor
   // Params:
   //    filename - the name of the from which data will be read
	TextFileReader(string filename);
   // Destructor
	~TextFileReader(void);
   // Reads the contents of the file and returns it as a single string
   // Returns:
   //    the contents of the file
	string readContents();
   // Reads the contents of the file, assuming the values are comma separated.
   // In the FloatDataArray, the array is allocated on the heap so should be deallocated.
   // Returns:
   //    A pointer to the data and the number of elements in the array
	FloatArrayData readFloatsCSV();

};

#endif

