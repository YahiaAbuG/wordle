wordle: wordle.o wordle_main.o
	gcc -Wall -std=c99 wordle.o wordle_main.o -o wordle
wordle.o: wordle.c wordle.h
	gcc -Wall -std=c99 -c wordle.c
wordle_main.o: wordle_main.c wordle.h
	gcc -Wall -std=c99 -c wordle_main.c
clean:
	rm *.o wordle