#ifndef _H_FILE
#define _H_FILE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class ProcessParams
{
public:
	ProcessParams(int c, int d, int p);

	friend std::ostream &operator<<(std::ostream& os, const ProcessParams& p);
	
	int getCreationTime() const;
	int getDuration() const;
	int getPriority() const;

private:	
	int creation_time;
	int duration; //seconds
	int priority;
};

class File
{

public:

	File();
	
	~File();

	void read_file();
	void print_processes_params();
	
	std::vector<ProcessParams *> getProcesses() const;

private:
	std::ifstream myfile; 
	std::vector<ProcessParams *> processes;
};


#endif