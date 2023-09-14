#ifndef _H_FILE
#define _H_FILE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p) { 
		creation_time = c;
		duration = d;
		priority = p;
	}

	friend ostream &operator<<(ostream& os, const ProcessParams& p) {
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
		return os;
	}
	
	int getCreationTime() const {
		return creation_time;
	}

	int getDuration() const {
		return duration;
	}

	int getPriority() const {
		return priority;
	}

private:	
	int creation_time;
	int duration; //seconds
	int priority;
};

class File
{

public:

	File() {
		myfile.open("entrada.txt");
		if (!myfile.is_open()) {
			cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	~File() {
		for(int i = 0; i < processes.size() ; i++) {
			ProcessParams *p = processes[i];
			delete p;
		}
	}

	void read_file() {
	
		int a, b, c;
		
		if (!myfile.is_open()) {
			cout << "Arquivo não está aberto!" << endl;
		}
		
		while (myfile >> a >> b >> c) {
			ProcessParams *p = new ProcessParams(a, b, c);
			processes.push_back(p);
		}

		cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
	}

	void print_processes_params() {
		vector<ProcessParams *>::iterator iter = processes.begin();

		for(iter; iter < processes.end(); iter++) {
			ProcessParams *p = *iter;
			cout << *p;
		}
	}


	vector<ProcessParams *> getProcesses() const {
		return processes;
	}

private:
	ifstream myfile; 
	vector<ProcessParams *> processes;
};


#endif