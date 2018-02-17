CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

assertions.o: assertions.h assertions.c
	gcc -c assertions.c -g $(CFLAGS)

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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomTest1: tests_random/randomtestcard1.c dominion.o rngs.o assertions.o
	gcc -o randomTest1 -g tests_random/randomtestcard1.c dominion.o rngs.o assertions.o $(CFLAGS)

randomTest2: tests_random/randomtestcard2.c dominion.o rngs.o assertions.o
	gcc -o randomTest2 -g tests_random/randomtestcard2.c dominion.o rngs.o assertions.o $(CFLAGS)

randomAdventurerTest: tests_random/randomtestadventurer.c dominion.o rngs.o assertions.o
	gcc -o randomTest3 -g tests_random/randomtestadventurer.c dominion.o rngs.o assertions.o $(CFLAGS)

randomtestcard1.out: dominion.o randomTest1
	./randomTest1 | grep -i -E 'FAIL|iteration|ANNOUNCEMENT' > randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: dominion.o randomTest2
	./randomTest2 | grep -i -E 'FAIL|iteration|ANNOUNCEMENT' > randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: dominion.o randomTest3
	./randomTest3 | grep -i -E 'FAIL|iteration|ANNOUNCEMENT' > randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtests: randomtestcard1.out randomtestcard2.out randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe *.exe badTestDrawCard randomTest1 randomTest2 randomTest3 randomTest4 randomAdventurerTest
