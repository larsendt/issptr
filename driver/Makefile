CPP = clang++
CFLAGS = -g -Wall

OBJS = main.o stepper.o sim_gpio.o

all: issptrdriver

issptrdriver: $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o issptrdriver

%.o: %.cpp %.h
	$(CPP) $(CFLAGS) -c -o $@ $<


