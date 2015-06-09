

clock : pangea_clock.o menu0.o menu1.o menu18.o menu19.o menu28.o
	cc -o clock pangea_clock.o menu0.o menu1.o menu18.o menu19.o menu28.o -ldispsw

pangea_clock.o : pangea_clock.c pangea_clock.h types.h
	cc -Wall -c pangea_clock.c

menu0.o : menu0.c pangea_clock.h types.h  
	cc -Wall -c menu0.c

menu1.o : menu1.c pangea_clock.h types.h
	cc -Wall -c menu1.c

menu18.o : menu18.c pangea_clock.h types.h
	cc -Wall -c menu18.c

menu19.o : menu19.c pangea_clock.h types.h
	cc -Wall -c menu19.c

menu28.o : menu28.c pangea_clock.h types.h
	cc -Wall -c menu28.c



