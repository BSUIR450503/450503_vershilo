#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main()
{
	HANDLE semaphore[2];
	LPSTR pipeName = "\\\\.\\pipe\\$MyPipe$";
	HANDLE hNamedPipe;
	DWORD cbRead;

	semaphore[0] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "semaphore0");
	semaphore[1] = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "semaphore1");

	hNamedPipe = CreateFile(pipeName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	char string[50];

	while(1)
	{
		WaitForSingleObject(semaphore[0], INFINITE);

		ReadFile(hNamedPipe, string, 512, &cbRead, NULL);

		if(!strcmp(string, "quit"))
			break;

		printf("Client process.String:");

		printf("%s\n\n", string);

		ReleaseSemaphore(semaphore[1], 1, NULL);
	}

	CloseHandle(hNamedPipe);
	for(int i = 0 ; i < 2; i ++){
		CloseHandle(semaphore[i]);
	}

	return 0;
}