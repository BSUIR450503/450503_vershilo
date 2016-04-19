#include "libra.h"

Myprocess::Myprocess(){
	input = 0;
	output = 0;
}

Myprocess::Myprocess(double _input){
	input = _input;
	output = 0;
}

void Myprocess::show(){
	cout << "Result: " << output << endl << endl;
}

void Myprocess::proces(){
	fstream input_file;
	input_file.open("temp", ios::app | ios::binary);
	input_file >> input;
	input_file.close();

#ifdef _WIN32
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	TCHAR CommandLine[] = TEXT("Project5.exe");
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, 
		CommandLine, 
		NULL, 
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi)){
		cout << "CreateProcess failed!";
		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE );
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
#endif

#ifdef linux
	pid_t pid; int status;
	switch(pid = fork()) {
	case -1:
		perror("fork");
		cout << "Error!";
		exit(1);
	case 0:
		execl("processB", "one", "two", "t", NULL);
		exit(0);
	default:
		wait(&status);
	}
#endif

	fstream output_file;
	output_file.open("temp", ios::in | ios::binary);
	output_file >> output;
	output_file.close();
	remove("temp");
}
