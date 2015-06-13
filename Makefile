

clock : pangea_clock.o menu0.o menu1.o menu5.o menu6.o menu7.o
	cc -o clock pangea_clock.o menu0.o menu1.o menu5.o menu6.o menu7.o -ldispsw

pangea_clock.o : pangea_clock.c pangea_clock.h types.h
	cc -Wall -c pangea_clock.c

menu0.o : menu0.c pangea_clock.h types.h  
	cc -Wall -c menu0.c

menu1.o : menu1.c pangea_clock.h types.h
	cc -Wall -c menu1.c

menu5.o : menu5.c pangea_clock.h types.h
	cc -Wall -c menu5.c

menu6.o : menu6.c pangea_clock.h types.h
	cc -Wall -c menu6.c

menu7.o : menu7.c pangea_clock.h types.h
	cc -Wall -c menu7.c



