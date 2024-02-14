CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG
AR = ar

OBJS=bit_map.o

HEADERS=bit_map.h

LIBS=

BINS=

.phony: clean all

all:	$(LIBS) $(BINS)

%.o:	$.c $(HEADERS)
		$(CC) $(CCOPTS) -c -o $@ $<

clean:
		rm -rf *.o *~ $(LIBS) $(BINS)
