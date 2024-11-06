/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmReadWrite.h"

#include "convertpgm.h"

int main(int argc, char **argv){ 
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

	/* convert binary to ascii using this function */
	int err = pgmb2a(pgm, argv[1]);
	if(err != 0)

		/* if have error when converting return error */

		return err;

	/* if success converting then write the file */
	err = Writefunction(pgm, argv[2]);

	/* return error if have */
	if(err != 0)
		return err;

	/* free the structure */
	free(pgm);

	/* success converting and return success */
	printf("CONVERTED");
	return 0;
}
