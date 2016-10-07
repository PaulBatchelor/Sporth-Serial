LDFLAGS=-lsporth -lsoundpipe -ljack -lsndfile -lm -lpthread

serial.so: serial.c
	$(CC) $^ $(LDFLAGS) -shared -fPIC -o $@

clean: 
	rm -rf serial.so serial
