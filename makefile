CC=clang
RM=rm -f
FLAGS=-Wall -std=c99 -O2 -O3 -O1

SRC=tsfetch.c

OUT=tsfetch

all: fetch

fetch: $(SRC)
	$(CC) $(FLAGS) -o $(OUT) $(SRC)

clean:
	$(RM) $(OBJS) $(OUT)
