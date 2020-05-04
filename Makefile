all: huffman
huffman: huffman.c huffman.h
	gcc $@.c -o $@ -Wall -Werror
clean:
	rm huffman
