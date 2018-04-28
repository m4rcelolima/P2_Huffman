OBJS = *.c
DEPS = *.h

compile:
	gcc $(OBJS) $(DEPS) -o huffman