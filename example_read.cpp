#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include <serial.h>

int main()
{
	int portHandle = SerialOpen("/dev/ttyUSB0",B115200);	//Open port, device="/dev/ttyUSB0", baundrate=115200
	char *data = SerialRead(portHandle,40);			//receive max 40 chars
	printf("%s",data);					//printf data
	SerialClose(portHandle);				//close port
}
