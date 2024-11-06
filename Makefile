#Now we need one target for each object file
#Each object file depends on its own implementation (.c)
#and any interfaces (.h) that it uses
CC=gcc

CCFLAGS= -g -std=c99

MODULES=pgmReadWrite.o	convertpgm.o

MAINS=pgmEcho.o	pgmComp.o	pgma2b.o	pgmb2a.o	pgmReduce.o	pgmTile.o	pgmAssemble.o

TARGETS=pgmEcho	pgmComp	pgma2b pgmb2a	pgmReduce	pgmTile	pgmAssemble

all:	${TARGETS} 

clean: 
	rm	-f	${TARGETS} ${MAINS}	${MODULES}	*.o

pgmEcho:	pgmEcho.o	${MODULES}
	${CC}	${CCFLAGS}	-o	pgmEcho	pgmEcho.o	${MODULES}

#first the module with the main routine
#target	implementation	interfaces
pgmEcho.o: pgmEcho.c	pgmReadWrite.h  
#	tool	compile flags 	outputname		files to compile
	${CC}	-c 	${CCFLAGS}	-o	pgmEcho.o	pgmEcho.c

#the next programme's main routine
#target			implementation	interfaces
pgmReadWrite.o:	pgmReadWrite.c	pgmReadWrite.h
	#tool	compile flags 	outputname			files to compile
	${CC}	-c 	${CCFLAGS}	-o	pgmReadWrite.o	pgmReadWrite.c

pgmComp:		pgmComp.o	${MODULES}
	${CC}	${CCFLAGS}		-o	pgmComp	pgmComp.o	${MODULES}	

#the comparing module
#target			implementation	interfaces	
pgmComp.o:		pgmComp.c	pgmReadWrite.h	
	#tool	compile flags 	outputname		files to compile
	${CC}	-c	${CCFLAGS}	-o	pgmComp.o	pgmComp.c 

pgma2b:		pgma2b.o	${MODULES}
	${CC}	${CCFLAGS}		-o	pgma2b	pgma2b.o	${MODULES}	

#the converting moudle
#target			implementation	interfaces
pgma2b.o:		pgma2b.c	pgmReadWrite.h	convertpgm.h
	#tool	compile flags 	outputname		files to compile	
	${CC}	-c	${CCFLAGS}	-o	pgma2b.o	pgma2b.c 

pgmb2a:		pgmb2a.o	${MODULES}
	${CC}	${CCFLAGS}		-o	pgmb2a	pgmb2a.o	${MODULES}	

#the converting moudle
#target			implementation	interfaces
pgmb2a.o:		pgmb2a.c	pgmReadWrite.h	convertpgm.h
	#tool	compile flags 	outputname		files to compile
	${CC}	-c	${CCFLAGS}	-o	pgmb2a.o	pgmb2a.c 

#the converting moudle
#target			implementation	interfaces
convertpgm.o:		convertpgm.c	pgmReadWrite.h	convertpgm.h
	#tool	compile flags 	outputname		files to compile
	${CC}	-c	${CCFLAGS}	-o	convertpgm.o	convertpgm.c 

pgmReduce:		pgmReduce.o	${MODULES}
	${CC}	${CCFLAGS}		-o	pgmReduce	pgmReduce.o	${MODULES}

#the reducing moudle
#target			implementation	interfaces		
pgmReduce.o:	pgmReduce.c	pgmReadWrite.h	
	#tool	compile flags 	outputname		files to compile
	${CC}	-c	${CCFLAGS}	-o	pgmReduce.o	pgmReduce.c 

pgmTile:	pgmTile.o	${MODULES}
	${CC}	${CCFLAGS}	-o	pgmTile	pgmTile.o	${MODULES}

#the tiling moudle
#target		implementation	interfaces		
pgmTile.o:	pgmTile.c		pgmTile.h	
	#tool	compile flags 	outputname		files to compile
	${CC}	-c	${CCFLAGS}	-o	pgmTile.o	pgmTile.c 

pgmAssemble:	pgmAssemble.o	${MODULES}
	${CC}	${CCFLAGS}	-o	pgmAssemble	pgmAssemble.o	${MODULES}

#the assemble moudle
#target		implementation	interfaces		
pgmAssemble.o:	pgmAssemble.c		pgmAssemble.h	
	#tool	compile flags 	outputname		files to compile
	${CC}	-c	${CCFLAGS}	-o	pgmAssemble.o	pgmAssemble.c 
