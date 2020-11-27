CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra \
	-pedantic -ansi -Wfloat-equal
INCS = teletext_base.h teletext_library.h testing.h
SOURCES =  testing.c teletext_base.c teletext_library.c
LIBS =  `sdl2-config --libs` -lm
CC = gcc


all: testing testing_d

testing: $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o testing $(CFLAGS) $(LIBS)

testing_d: $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o testing_d -g -O $(CFLAGS) $(LIBS)

run: all
	./testing test.m7

memchk: testing_d
	valgrind --error-exitcode=1 --quiet --leak-check=full \
	./testing_d test.m7

clean:
	rm -f testing testing_d
