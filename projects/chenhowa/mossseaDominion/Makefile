CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

assertions_better.o: assertions_better.h assertions_better.c;
	gcc -c assertions_better.c -g $(CFLAGS)

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

unittestresults.out: unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4 dominion.o
	echo "unittest1.c: " > unittestresults.out
	./unitTest1 >> unittestresults.out
	echo "unittest2.c: " >> unittestresults.out
	./unitTest2 >> unittestresults.out
	echo "unittest3.c: " >> unittestresults.out
	./unitTest3 >> unittestresults.out
	echo "unittest4.c: " >> unittestresults.out
	./unitTest4 >> unittestresults.out
	echo "cardtest1.c: " >> unittestresults.out
	./cardTest1 >> unittestresults.out
	echo "cardtest2.c: " >> unittestresults.out
	./cardTest2 >> unittestresults.out
	echo "cardtest3.c: " >> unittestresults.out
	./cardTest3 >> unittestresults.out
	echo "cardtest4.c: " >> unittestresults.out
	./cardTest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

quiettests: unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4 dominion.o
	echo "unittest1.c: " > unittestresults.out
	./unitTest1 | grep -E -i "success|warning" >> unittestresults.out
	echo "unittest2.c: " >> unittestresults.out
	./unitTest2 | grep -E -i "success|warning" >> unittestresults.out
	echo "unittest3.c: " >> unittestresults.out
	./unitTest3 | grep -E -i "success|warning" >> unittestresults.out
	echo "unittest4.c: " >> unittestresults.out
	./unitTest4 | grep -E -i "success|warning" >> unittestresults.out
	echo "cardtest1.c: " >> unittestresults.out
	./cardTest1 | grep -E -i "success|warning" >> unittestresults.out
	echo "cardtest2.c: " >> unittestresults.out
	./cardTest2 | grep -E -i "success|warning" >> unittestresults.out
	echo "cardtest3.c: " >> unittestresults.out
	./cardTest3 | grep -E -i "success|warning" >> unittestresults.out
	echo "cardtest4.c: " >> unittestresults.out
	./cardTest4 | grep -E -i "success|warning" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomTest1: tests_random/randomtestcard1.c dominion.o rngs.o assertions_better.o
	gcc -o randomTest1 -g tests_random/randomtestcard1.c dominion.o rngs.o assertions_better.o $(CFLAGS)

randomTest2: tests_random/randomtestcard2.c dominion.o rngs.o assertions_better.o
	gcc -o randomTest2 -g tests_random/randomtestcard2.c dominion.o rngs.o assertions_better.o $(CFLAGS)

randomAdventurerTest: tests_random/randomtestadventurer.c dominion.o rngs.o assertions_better.o
	gcc -o randomAdventurerTest -g tests_random/randomtestadventurer.c dominion.o rngs.o assertions_better.o $(CFLAGS)

randomtestcard1.out: dominion.o randomTest1
	./randomTest1 | grep -i -E 'FAIL|iteration|ANNOUNCEMENT' > randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: dominion.o randomTest2
	./randomTest2 | grep -i -E 'FAIL|iteration|ANNOUNCEMENT' > randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: dominion.o randomAdventurerTest
	./randomAdventurerTest | grep -i -E 'FAIL|iteration|ANNOUNCEMENT' > randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtests: randomtestcard1.out randomtestcard2.out randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard *.exe badTestDrawCard unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4 randomTest1 randomTest2 randomTest4 randomAdventurerTest
