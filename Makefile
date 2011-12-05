
CC=$(CROSS_COMPILE)gcc -g
TARGET=libserial

libserial.o:libserial.c
	$(CC) -c libserial.c

install: libserial.o
	$(CROSS_COMPILE)ar rcs lib$(TARGET).a libserial.o
	install lib$(TARGET).a /usr/lib/lib$(TARGET).a
	install *.h /usr/include/

example:example_write example_read

example_write:example_write.cpp
	$(CC) example_write.cpp -llibserial -o example_write

example_read:example_read.cpp 
	$(CC) example_read.cpp -llibserial -o example_read

