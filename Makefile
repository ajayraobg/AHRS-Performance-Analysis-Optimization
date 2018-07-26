CC = gcc
CFLAGS = -c -Wall -march=armv7-a -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a8 -mtune=cortex-a8 -O3 -g

PROF =  -pg -g # Add for gprof

%.o: %.c
	$(CC) $(CFLAGS) $(PROF) -c -o $@ $<

madgwick: main.o MadgwickAHRS.o 
	$(CC) $(PROF) main.o MadgwickAHRS.o -lrt -lm -static -o $@

MadgwickAHRS_list.s: MadgwickAHRS.c
	$(CC) -Wa,-adhln -g MadgwickAHRS.c -c > MadgwickAHRS_list.s

clean:
	rm -f *.o madgwick *.s
