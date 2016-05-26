#include "librariesh.h"
#include "func.cpp"

void main(int argc, char* argv[])
{
	Myprocess P;
	if (argc == 2)
	{
#ifdef _WIN32
		P.printString(atoi(argv[1]));
#endif
	}
	else P.Work_Process(argv[0]);
	return;
}