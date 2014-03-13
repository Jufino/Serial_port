#include "serial.h"
/*The MIT License (MIT)

Copyright (c) [2011] [Juraj Fojtik]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.   
*/
//--------------------------------------------------------
int SerialOpen(const char *port, speed_t speed) {
    int fd;
    fd = open(port, O_RDWR);
    if (fd < 0)	printf("open error %d %s\n", errno, strerror(errno));
    else
    {
        struct termios my_termios;
        tcgetattr(fd, &my_termios);
	//nastavenie rychlosti-----------------
    	cfsetispeed(&my_termios, speed);
    	cfsetospeed(&my_termios, speed);
	//-------------------------------------
	my_termios.c_cflag |= (CLOCAL | CREAD | CRTSCTS);
	//nieje parita,8N1
	my_termios.c_cflag &= ~PARENB;
	my_termios.c_cflag &= ~CSTOPB;
	my_termios.c_cflag &= ~CSIZE;
	my_termios.c_cflag |= CS8;
	//raw input and output
	my_termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	my_termios.c_oflag &= ~OPOST;
	//nieje software
	my_termios.c_iflag &= ~(IXON | IXOFF | IXANY);
	//-----------------------------------
	tcsetattr(fd, TCSANOW, &my_termios);
    }
    return fd;
}
//-----------------------------------------
void SerialClose(int port){
	close(port);
}
//-----------------------------------------
void SerialWrite(int port,char data[]){ 
	write(port,data,strlen(data));
}
//-----------------------------------------
char *SerialReadLine(int port,int max){
	int x=0;
	char *prijem_serial = (char*)malloc(sizeof(char)*max);
	char znak[1];
	while(1!=read(port, znak,1));
	while(znak[0]  != '\n'){
        	prijem_serial[x++] = znak[0];
		while(1!=read(port, znak,1));
	}
        prijem_serial[x]='\0';
	return prijem_serial;
}
char *SerialRead(int port,int pocet){
        int x=0;
        char *prijem_serial = (char*)malloc(sizeof(char)*pocet);
        char znak;
        while(x < pocet){
                if (read(port,&znak,1)>0)	prijem_serial[x++] = znak;
        }
        return prijem_serial;
}

