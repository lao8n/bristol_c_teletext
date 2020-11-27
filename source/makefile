CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra \
	-pedantic -ansi -Wfloat-equal
INCS = teletext_base.h teletext_library.h
SOURCES =  main.c teletext_base.c teletext_library.c
LIBS =  `sdl2-config --libs` -lm
CC = gcc

all: main main_d

main: $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o main $(CFLAGS) $(LIBS)

main_d : $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o main_d -g -O $(CFLAGS) $(LIBS)

run: all
	./main test.m7
	./main lfc.m7
	./main panda.m7

memchk: main_d
	valgrind --error-exitcode=1 --quiet --leak-check=full \
	./main_d test.m7

clean:
	rm -f main main_d
