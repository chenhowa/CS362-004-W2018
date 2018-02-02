CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)
assertions.o: assertions.h assertions.c 
	gcc -c assertions.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unitTest1: dominion.o rngs.o ./unit_tests/unittest1.c assertions.o 
	gcc -o unitTest1 -g ./unit_tests/unittest1.c dominion.o rngs.o assertions.o $(CFLAGS)

unitTest2: dominion.o rngs.o ./unit_tests/unittest2.c assertions.o 
	gcc -o unitTest2 -g ./unit_tests/unittest2.c dominion.o rngs.o assertions.o $(CFLAGS)

unitTest3: dominion.o rngs.o ./unit_tests/unittest3.c assertions.o 
	gcc -o unitTest3 -g ./unit_tests/unittest3.c dominion.o rngs.o assertions.o $(CFLAGS)

unitTest4: dominion.o rngs.o ./unit_tests/unittest4.c assertions.o 
	gcc -o unitTest4 -g ./unit_tests/unittest4.c dominion.o rngs.o assertions.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard *.exe badTestDrawCard unitTest1 unitTest2 unitTest3 unitTest4
