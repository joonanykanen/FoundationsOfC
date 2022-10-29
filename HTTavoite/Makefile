# HTTavoitetaso Makefile, tehnyt: Joona Nykänen (******) 5.3.2022

HTTavoitetaso: HTTavoitetaso.o HTTavoiteKirjasto.o HTPerusKirjasto.o
	gcc HTTavoitetaso.o HTTavoiteKirjasto.o HTPerusKirjasto.o -o HTTavoitetaso

HTTavoitetaso.o: HTTavoitetaso.c
	gcc HTTavoitetaso.c -c -std=c99 -pedantic -Wall

HTTavoiteKirjasto.o: HTTavoiteKirjasto.c
	gcc HTTavoiteKirjasto.c -c -std=c99 -pedantic -Wall

HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
	gcc HTPerusKirjasto.c -c -std=c99 -pedantic -Wall

clean:
	rm *.o HTTavoitetaso
