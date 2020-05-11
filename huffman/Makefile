all: huffman reader encoder
huffman: huffman.c huffman.h
	gcc $@.c -o $@ -Wall
encoder: encoder.c
	gcc $@.c -o $@ -Wall
reader: reader.c
	gcc $@.c -o $@ -Wall
clean:
	rm -f huffman reader encoder .in.txt .keys
