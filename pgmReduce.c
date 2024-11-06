/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmReadWrite.h"

#include "pgmReduce.h"
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
		printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm", argv[0]); 
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

	if(!atoi(argv[2]) || atoi(argv[2]) < 0 ){
		printf("ERROR: Miscellaneous");
		return 100;
	}
	error = ReadFunction(pgm, argv[1]);
	/* if read function not equal 0 means there is error, return that */ 
	if(error != 0)
		return error; 
	/* if no error keep on*/
	error = Reducefunction(pgm, atoi(argv[2]), argv[3]);

	/* if read function not equal 0 means there is error, return that */
	if(error != 0)
		return error; 
	/* if no error keep on*/
	/* free the structure*/
	/*print reduce*/
	printf("REDUCED");
	free(pgm); 
	return error; 
}

int Reducefunction(PGMStructure *pgm, int reduce_number, const char *fname){
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

		/* return an error code          */
		return OUTPUT_FAILED;
	} /* NULL output file */
	
	/* write magic number, size & gray value */
	width = (int)pgm->width/reduce_number;
	height = (int)pgm->height/reduce_number;

	if(pgm->width % reduce_number != 0){
		width += 1;
	}
	if(pgm->height % reduce_number != 0){
		height += 1;
	}

	maxGray = pgm->maxGray;
	size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n",pgm->magic_number[1], width, height, maxGray);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0){ 
	/* dimensional write failed    */
		/* free memory                   */
		free(pgm->commentLine);
		free(pgm->imageData);

		/* print an error message        */
		printf("ERROR: Output Failed (%s)", fname);

		/* return an error code          */
		return OUTPUT_FAILED;
	} /* dimensional write failed    */

        /* pointer for efficient write code      */
	if(pgm->magic_number[1] == '2'){
		for (int i = 0; i < pgm->height; i++)
		{
			int count = 0;
			for (int j = 0; j < pgm->width; j++)
			{
				if( i % reduce_number == 0 && j % reduce_number == 0)
				{
					/* per gray value */
					count++;
					/* get next char's column        */
					int nextCol = ( count / width -1);
					/* write the entry & whitespace  */
					nBytesWritten = fprintf(outputFile, "%d%c", pgm->imageData[i][j], (nextCol ? ' ' : '\n') );

					/* sanity check on write         */
					if (nBytesWritten < 0)
						{ /* data write failed   */
						/* free memory           */
						free(pgm->commentLine);
						free(pgm->commentLine);

						/* print error message   */
						printf("ERROR: Output Failed (%s)", fname);

						/* return an error code  */
						return OUTPUT_FAILED;
						} /* data write failed   */
				}
			} /* per gray value */
		}
	}
	else if(pgm->magic_number[1] == '5'){
		for (int i = 0; i < pgm->height; i++)
		{
			for (int j = 0; j < pgm->width; j++)
			{
				if( i % reduce_number == 0 && j % reduce_number == 0)
				{
					nBytesWritten = fwrite(&pgm->imageData[i][j], sizeof(unsigned char), 1 , outputFile);
					if (nBytesWritten < 0)
						{ /* data write failed   */
						/* free memory           */
						free(pgm->commentLine);
						free(pgm->commentLine);

						/* print error message   */
						printf("ERROR: Output Failed (%s)", fname);

						/* return an error code  */
						return OUTPUT_FAILED;
						} /* data write failed   */
					}
			}
		}
	}
	else{
		fclose(outputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", fname);
        
		/* and return                    */
		return EXIT_BAD_MAGIC_NUMBER;
		/* failed magic number check   */
		/* create an array for the pgm file */
		int column = 0;
		int row = 0;
		/*If the column is longer than the width*/
		if(pgm->width < column){
			column = 0;
			row++;
		}

		

	}
	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
} 