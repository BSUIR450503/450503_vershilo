#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

CRITICAL_SECTION critSection;
bool closeThread[10];

struct args{
	char string[30];
	int numb;
};

DWORD WINAPI print(LPVOID arg){
	char str[30];
	int numb;

	strcpy(str,(*(args*)arg).string);
	numb = (*(args*)arg).numb;

	while(1){		
		Sleep(1000);
		if(closeThread[numb] == true){
			break;
		}
		EnterCriticalSection(&critSection);
		printf("%s",str);
		LeaveCriticalSection(&critSection);
	}

	return 0;
}

int getchNonStop() 
{
    if (_kbhit())
        return _getch();
    else
        return -1;
}

int main(){

	char string[10][30] = {{"First thread\n"},{"Second thread\n"},{"Third thread\n"},{"Fourth thread\n"},{"Fifth thread\n"},
	{"Sixth thread\n"},{"Seventh thread\n"},{"Eighth thread\n"},{"Ninth thread\n"},{"Tenth thread\n"}};

	HANDLE hThread[10];
	DWORD idThread[10];
	int count = 0;

	InitializeCriticalSection(&critSection);

	while(1){
		int ch = getchNonStop();
		switch(ch){
			case '+':
				if(count < 10){
					closeThread[count] = false;
					struct args *arg = (struct args*)malloc(sizeof(args));
					(*arg).numb = count;
					strcpy((*arg).string,string[count]);
					count++;
					hThread[count-1] = CreateThread(NULL,0,print,(void*)arg,0,&idThread[count-1]);
				}
				break;
			case '-':
				if(count > 0){
					count--;
					closeThread[count] = true;
				}
				break;
			case 'q':
				while(count > 0){
					count--;
					closeThread[count] = true;
				}

				WaitForSingleObject(hThread[0],INFINITE);

				DeleteCriticalSection(&critSection);
				return 0;
				break;
		}
	}
}