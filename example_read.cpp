#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include "libserial.h";

int main(void)
{
	char receive_data[40];
	memset(&receive_data, 0, sizeof(receive_data));		//clear array

	int port_int = open_serial("/dev/ttyUSB0",B115200);	//open port
	
	read_serial(port_int,receive_data,40);		//receive data
	printf(receive_dat);				//printf receive data
	
	close_serial(port_int);				//close port
}
