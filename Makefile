CC=$(CROSS_COMPILE)g++ -Wall -g
TARGET=serial

serial:serial.c
	$(CC) -c serial.c

install: $(TARGET)
	$(CROSS_COMPILE)ar rcs lib$(TARGET).a serial.o
	install lib$(TARGET).a /usr/lib/lib$(TARGET).a
	install *.h /usr/include/
	rm libserial.a
	rm serial.o

clean:
	rm /usr/lib/lib$(TARGET).a
	rm /usr/include/$(TARGET).h

example:example_write example_read

example_write:example_write.cpp
	$(CC) example_write.cpp -lserial -o example_write

example_read:example_read.cpp 
	$(CC) example_read.cpp -lserial -o example_read

