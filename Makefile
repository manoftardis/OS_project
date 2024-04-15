CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG
AR=ar

OBJS=bitmap.o\
	 buddy_allocator.o\
	 mmap_allocator.o\
	 pseudo_malloc.o\

HEADERS=bitmap.h buddy_allocator.h mmap_allocator.h pseudo_malloc.h

LIBS=libbuddy.a

BINS=buddy_allocator_test\
	 driver

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	$.c $(HEADERS)
		$(CC) $(CCOPTS) -c -o $@ $<

libbuddy.a: $(OBJS)
		$(AR) -rcs $@ $^
		$(RM) $(OBJS)

buddy_allocator_test: buddy_allocator_test.o $(LIBS)
		$(CC) $(CCOPTS) -o $@ $^ -lm

driver: driver.o $(LIBS)
		$(CC) $(CCOPTS) -o $@ $^ -lm

clean:
		rm -rf *.o *~ $(LIBS) $(BINS)
