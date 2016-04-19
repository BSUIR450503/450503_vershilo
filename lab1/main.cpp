#include "libra.h"
#include <conio.h>

int main(int argc, char *argv[]) {
	
	double i = 0;
	fstream input_file;
	input_file.open("temp", ios::app | ios::binary);
	input_file << i;
	input_file.close();
	char c;
 
	do{
	c = getch();

	if (c == 43){			//	if+
		Myprocess proc(i);
		proc.proces();
		proc.show();
	}

	if (c == 45){			//	if -
		
	}

	if (c == 27){			//	if ESC
		return 0;
	}
	}while(1);
	
	return 0;
}
