CC=gcc
RM=rm -f


SRCS=sort_algorithms.c utils.c main.c
OBJS=$(SRCS:.c=.o)


all: main


main: $(OBJS)
	$(CC) -o main $(OBJS)


.c.o:
	$(CC) -o $@ -c $< 


clean:
	$(RM) $(OBJS)


distclean: clean
	$(RM) main


.PHONY: all main distclean clean
