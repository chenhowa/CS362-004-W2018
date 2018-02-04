CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

assertions.o: assertions.h assertions.c 
	gcc -c assertions.c -g $(CFLAGS)

logMisMatch.o: logMismatch.h logMismatch.c 
	gcc -c logMismatch.c -g $(CFLAGS)

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

cardTest1: dominion.o rngs.o ./unit_tests/cardtest1.c assertions.o logMismatch.o
	gcc -o cardTest1 -g ./unit_tests/cardtest1.c dominion.o rngs.o assertions.o logMismatch.o $(CFLAGS)

cardTest2: dominion.o rngs.o ./unit_tests/cardtest2.c assertions.o logMismatch.o
	gcc -o cardTest2 -g ./unit_tests/cardtest2.c dominion.o rngs.o assertions.o logMismatch.o $(CFLAGS)

cardTest3: dominion.o rngs.o ./unit_tests/cardtest3.c assertions.o logMismatch.o
	gcc -o cardTest3 -g ./unit_tests/cardtest3.c dominion.o rngs.o assertions.o logMismatch.o $(CFLAGS)

cardTest4: dominion.o rngs.o ./unit_tests/cardtest4.c assertions.o logMismatch.o
	gcc -o cardTest4 -g ./unit_tests/cardtest4.c dominion.o rngs.o assertions.o logMismatch.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard > unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4
	./unitTest1 > unittestresults.out
	./unitTest2 >> unittestresults.out
	./unitTest3 >> unittestresults.out
	./unitTest4 >> unittestresults.out
	./cardTest1 >> unittestresults.out
	./cardTest2 >> unittestresults.out
	./cardTest3 >> unittestresults.out
	./cardTest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

quiettests: unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4
	./unitTest1 | grep -E -i "success|warning" > unittestresults.out
	./unitTest2 | grep -E -i "success|warning" >> unittestresults.out
	./unitTest3 | grep -E -i "success|warning" >> unittestresults.out
	./unitTest4 | grep -E -i "success|warning" >> unittestresults.out
	./cardTest1 | grep -E -i "success|warning" >> unittestresults.out
	./cardTest2 | grep -E -i "success|warning" >> unittestresults.out
	./cardTest3 | grep -E -i "success|warning" >> unittestresults.out
	./cardTest4 | grep -E -i "success|warning" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard *.exe badTestDrawCard unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4
