CPP = g++
CFLAGS = -g -Wall -I/usr/local/include
LIBS=-L/usr/local/lib -lwiringPi
OBJS = main.o stepper.o magnetometer.o

all: issptrdriver

issptrdriver: $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o issptrdriver $(LIBS)

%.o: %.cpp %.h
	$(CPP) $(CFLAGS) -c -o $@ $<


.PHONY clean:
	rm -f *.o issptrdriver
