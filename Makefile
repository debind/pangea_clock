

clock : clock.o enc.o main.o menu.o seg7.o 
	cc -o clock clock.o main.o menu.o seg7.o enc.o -lwiringPi

clock.o : clock.c types.h clock.h
	cc -Wall -c clock.c

enc.o : enc.c types.h enc.h
	cc -Wall -c enc.c

main.o : main.c types.h enc.h clock.h menu.h
	cc -Wall -c main.c

menu.o : menu.c types.h menu.h enc.h clock.h
	cc -Wall -c menu.c

seg7.o : seg7.h types.h 
	cc -Wall -c seg7.c


