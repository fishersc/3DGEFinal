#include "TextFileReader.h"
#include <fstream>
#include <iostream>
using std::ifstream;
using std::getline;
using std::cout;
using std::endl;

TextFileReader::TextFileReader(string filename)
{
	contents = "";
	this->filename = filename;
}


TextFileReader::~TextFileReader(void)
{
}

string TextFileReader::readContents()
{
	contents = "";
	string line;
	ifstream fin(filename.c_str());
	if(fin.is_open()){
		while(fin.good()){
			getline(fin, line);
			contents += line + "\n";
		}
		fin.close();
	}else{
		cout << "Cannot open file." << endl;
	}
	return contents;
}

FloatArrayData TextFileReader::readFloatsCSV()
{
	values.clear();
	string value;
	ifstream fin(filename.c_str());
	if(fin.is_open()){
		while(fin.good()){
			getline(fin, value, ',');
			values.push_back((float)atof(value.c_str()));
		}
		fin.close();
	}else{
		cout << "Cannot open file." << endl;
	}
	
	FloatArrayData data = { NULL, values.size() };
	if(values.size() > 0){
		data.arr = new float[data.count];
		for(int i = 0; i < data.count; i++){
			data.arr[i] = values[i];
		}
	}
	return data;
}
