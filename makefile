CC=clang
RM=rm -f
FLAGS=-Wall -std=c99

SRCS=fetch.c
OBJS=$(subst .c,.o,$(SRCS))

OUT=a.out

all: fetch

fetch: $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $(OBJS)

fetch.o: fetch.c fetch.h

clean:
	$(RM) $(OBJS) $(OUT)