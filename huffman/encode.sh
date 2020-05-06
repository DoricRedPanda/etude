#!/bin/sh
INPUT=.in.txt
KEYS=.keys
if [ $# -eq 1 ]; then
	./reader < $1 | ./huffman > $KEYS && ./encoder $KEYS < $1
else
	./reader $INPUT | ./huffman > $KEYS && ./encoder $KEYS < $INPUT
fi
