PROG = hex2bits
CFLAGS ?= -W

all: $(PROG)
	$(RUN) ./$(PROG)

$(PROG): src/main.cpp Makefile
	$(CXX) src/main.cpp src/jfs_std_lib.cpp $(CFLAGS) -o $@

clean:
	rm -rf $(PROG) *.o
