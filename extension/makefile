CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra \
	-pedantic -ansi -Wfloat-equal
INCS = extension.h teletext_library.h teletext_base.h
SOURCES =  testing_extension.c extension.c \
	teletext_library.c teletext_base.c
LIBS =  `sdl2-config --libs` -lm
CC = gcc


all: testing_extension

testing_extension: $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o testing_extension $(CFLAGS) \
	$(LIBS)

run: all
	./testing_extension

clean:
	rm -f testing_extension
