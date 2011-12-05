#ifndef _LIBSERIAL_H
#define _LIBSERIAL_H

#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls
#include <errno.h>
#include <stdio.h>
//--------------------------------------------------------
int open_serial(const char *port, speed_t speed);
//-----------------------------------------
void close_serial(int port);
//-----------------------------------------
void write_serial(int port,char data[]);
//------------------------------------------
void read_serial(int port,char prijem_data[], int poc);
//------------------------------------------

#endif
