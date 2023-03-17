CC=gcc
CFLAGS=-Wall -Werror
SOURCE_FILES=$(addprefix Src/, Main.c Primality.c)

.PHONY: debug
debug: $(SOURCE_FILES)
	$(CC) $(CFLAGS) -g -o buutti $^
.PHONY: stable
stable: $(SOURCE_FILES)
	$(CC) $(CFLAGS) -O3 -o buutti $^
.PHONY: clean
clean:
	rm -vfr *~ buutti
