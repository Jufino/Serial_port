#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include "libserial.h";

int main(void)
{
	int port_int = open_serial("/dev/ttyUSB0",B115200);	//open port
	
	write_serial(port_int,"test");		//write "test" to serial port

	close_serial(port_int);		//close port
}
