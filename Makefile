LDFLAGS=-lsporth -lsoundpipe -ljack -lsndfile -lm -lpthread

#PROJECT=TEST1
#PROJECT=TEST2
#PROJECT=TEST3

# Project 4 must have the arduino sketch 
# macro PUSH_BUTTON defined 

PROJECT=TEST4

CFLAGS=-D$(PROJECT)

default: serial serial.so

serial.so: serial.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -shared -fPIC -o $@

serial: serial.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -DSTANDALONE -o $@

clean: 
	rm -rf serial.so serial
