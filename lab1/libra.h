#pragma once
#include <iostream>
#include <string>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

using namespace std;

class Myprocess{
private:
	double input;
	double output;

public:
	Myprocess();
	Myprocess(double);
	~Myprocess(){};

	void show();
	void proces();
};