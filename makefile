OBJS = src/*.c
DEPS = src/*.h

compile:
	gcc $(OBJS) $(DEPS) -o huffman