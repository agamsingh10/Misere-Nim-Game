all:  nim.c
	clang -Wall -pedantic -std=c99 nim.c -c

nim.o:  nim.c
	clang -Wall -pedantic -std=c99 nim.c -c

clean:  
	rm *.o