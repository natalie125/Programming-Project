/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmReadWrite.h"

#include "convertpgm.h"

int pgma2b(PGMStructure *pgm, const char *fname){
	int count = ReadFunction(pgm, fname);
	if(count == 0){
		if(pgm->magic_number[1] == '2'){
			pgm->magic_number[1] = '5';
			return 0;
		}
		else{
			printf("ERROR: Bad Magic Number (%s)", fname);
			return EXIT_BAD_MAGIC_NUMBER; 
		}
	}
}
int pgmb2a(PGMStructure *pgm, const char *fname){
	int count = ReadFunction(pgm, fname);
	if(count == 0){
		if(pgm->magic_number[1] == '5'){
			pgm->magic_number[1] = '2';
			return 0;
		}
		else{
			printf("ERROR: Bad Magic Number (%s)", fname);
			return EXIT_BAD_MAGIC_NUMBER; 
		}
	}
}