CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)

run: testme
	./testme

clean:
	rm -f *.o *.exe testme *.gcno *.gcda
