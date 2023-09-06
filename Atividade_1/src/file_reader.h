#ifndef _H_FILE_READER
#define _H_FILE_READER

#include <vector>
#include <string>

class FileReader
{

private:

public:

	FileReader();
	~FileReader();
	
	std::vector<std::string> read(std::string path);

};

#endif