CC=gcc
CFLAGS="-Wall -Werror"

.PHONY: debug
debug: Main.c
	$(CC) $(CFLAGS) -g -o buutti Main.c
.PHONY: stable
stable: Main.c
	$(CC) $(CFLAGS) -O3 -o buutti Main.c
.PHONY: clean
clean:
	rm -vfr *~ buutti
