all: huffman reader encoder
huffman: huffman.c huffman.h
	gcc $@.c -o $@ -Wall -Werror
encoder: encoder.c
	gcc $@.c -o $@ -Wall -Werror
reader: reader.c
	gcc $@.c -o $@ -Wall -Werror
clean:
	rm -f huffman reader encoder .in.txt .keys
