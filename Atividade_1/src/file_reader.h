#ifndef _H_FILE_READER
#define _H_FILE_READER

#include <vector>
#include <string>

class FileReader
{

public:

	FileReader();
	~FileReader();
	
	std::vector<std::vector<int>>  read(std::string path);

};

#endif