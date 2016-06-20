#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

PROCESS_INFORMATION createProcess() {
	STARTUPINFO stInfo;
	PROCESS_INFORMATION prInfo;
	ZeroMemory(&stInfo, sizeof(stInfo));
	stInfo.cb = sizeof(stInfo);
	
	char* cmd = "D:\\new\\spovm_2\\Debug\\Child.exe";

	CreateProcess(NULL, cmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &stInfo, &prInfo);

	return prInfo;
}

int main()
{
	HANDLE semaphore[2];
	HANDLE hNamedPipe;
	LPSTR pipeName = "\\\\.\\pipe\\$MyPipe$";
	DWORD cbWritten;
	PROCESS_INFORMATION info;

	hNamedPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, PIPE_UNLIMITED_INSTANCES, 0, 0, 0, NULL);
                                      
	CreateSemaphore(NULL, 1, 1, "semaphore0");
	CreateSemaphore(NULL, 0, 1, "semaphore1");

	semaphore[0] = OpenSemaphore(SEMAPHORE_ALL_ACCESS,TRUE, "semaphore0");
	semaphore[1] = OpenSemaphore(SEMAPHORE_ALL_ACCESS,TRUE, "semaphore1");

	info = createProcess();

	ConnectNamedPipe(hNamedPipe, NULL);

	char string[50];

	while(1)
	{
		printf("Server process.Enter a string:");
		scanf("%s", &string);

		WriteFile(hNamedPipe, string, strlen(string) + 1, &cbWritten, NULL);	

		ReleaseSemaphore(semaphore[0],1,NULL);

		if(!(strcmp(string, "quit")))
		{
			WaitForSingleObject(info.hProcess, INFINITE);
			break;
		}

		WaitForSingleObject(semaphore[1], INFINITE);
	}

	CloseHandle(info.hProcess);
	CloseHandle(hNamedPipe);
	for(int i = 0 ; i < 2; i ++){
		CloseHandle(semaphore[i]);
	}

	return 0;
} 