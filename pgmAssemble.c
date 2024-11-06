/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmReadWrite.h"

#include "pgmAssemble.h"
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
		printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+"); 
		/* return no error*/
		return EXIT_NO_ERRORS; 
	}
	else if (argc != 4)	{ 
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
	error = Assemblefunction(pgm, atoi(argv[2]), argv[3]);

	/* if read function not equal 0 means there is error, return that */
	if(error != 0)
		return error; 
	/* if no error keep on*/
	/* free the structure*/
	free(pgm); 
	return error; 
}

int Assemblefunction(PGMStructure *pgm, int ass_number, const char *fname){
	int width, height, maxGray;
	/* open a file for writing               */
	FILE *outputFile = fopen(fname, "w");

	/* check whether file opening worked     */
	if (outputFile == NULL){ 
		/* NULL output file */
		/* free memory                   */
		free(pgm->commentLine);
		free(pgm->imageData);

		/* print an error message        */
		printf("ERROR: Output Failed (%s)", fname);	
		return 1;
		/* return an error code          */
		return OUTPUT_FAILED;
	} /* NULL output file */
	
	
	
	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;

} 