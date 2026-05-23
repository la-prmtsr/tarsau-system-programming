CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude

SRC=src/main.c src/archive.c src/extract.c src/utils.c

OUT=tarsau

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT) *.sau