#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include <serial.h>

int main(void)
{
	int portHandle = SerialOpen("/dev/ttyUSB0",B115200);	//Open port, device="/dev/ttyUSB0", baundrate=115200
	SerialWrite(portHandle,"test");				//write "test" to serial port
	SerialClose(portHandle);				//close port
}
