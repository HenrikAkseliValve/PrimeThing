CC=gcc
CFLAGS="-Wall"

debug:clean
	$(CC) $(CFLAGS) -g -o buutti main.c
stable:clean
	$(CC) $(CFLAGS) -o buutti main.c
clean:
	rm -vfr *~ buutti
