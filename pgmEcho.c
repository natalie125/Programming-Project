/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Natalie LEUNG                  */
/***********************************/

/***********************************/
/* A first iteration to take a pgm */
/* file in binary and convert to   */
/* ASCII or vice versa             */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmReadWrite.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
	{ /* main() */
	/* check for correct number of arguments */
	int error = 0; 

	/* use this int error to check the return function, if not 0 return */
	PGMStructure *pgm = malloc(sizeof(PGMStructure));
	Structure(pgm);

	if (argc == 1){
		/* check if argument is 0*/
		/* return special message indicating the correct usage and return 0*/
		printf("Usage: %s inputImage.pgm outputImage.pgm", argv[0]); 

		/* return no error*/
		return EXIT_NO_ERRORS; 
	}
	else if (argc != 3)	{ 
	/* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count");

		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;

	} /* wrong arg count */
	error = ReadFunction(pgm, argv[1]);

	/* if read function not equal 0 means there is error, return that */ 
	if(error != 0)
		return error; 

	/* if no error keep on*/
	error = Writefunction(pgm, argv[2]);

	/* if read function not equal 0 means there is error, return that */
	if(error != 0)
		return error; 
	
	/* if no error keep on*/
	/* free the structure*/
	free(pgm); 
	return error; 
}

