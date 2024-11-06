/* this function is fopr defining structure in pointer PGMStructure */
#include "pgmReadWrite.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void Structure(PGMStructure *pgm){
	/* the magic number		         */
	/* stored as two bytes to avoid	         */
	/* problems with endianness	         */
	/* Raw:    0x5035 or P5		         */
	/* ASCII:  0x5032 or P2		         */

	pgm->magic_number[0] = '0';
	pgm->magic_number[1] = '0';

	/* we will store ONE comment	         */
	pgm->commentLine = NULL;

	/* the logical width & height	         */
	/* note: cannot be negative	         */
	pgm->width = 0;
	pgm->height = 0;

	/* maximum gray value (assumed)	         */
	/* make it an integer for ease	         */
	pgm->maxGray = 255;
	/* pointer to raw image data	         */
	pgm->imageData = NULL;
}

int ReadFunction(PGMStructure *pgm, const char *fname){
/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */

	FILE *inputFile = fopen(fname, "r");

	/* if it fails, return error code        */
	if (inputFile == NULL){
		printf("ERROR: Bad File Name (%s)", fname);
        	return EXIT_BAD_FILE_NAME;
	}
	/* read in the magic number              */
	pgm->magic_number[0] = getc(inputFile);
	pgm->magic_number[1] = getc(inputFile);

	unsigned short *magic_Number = (unsigned short *) pgm->magic_number;

	/* sanity check on the magic number      */
	if(pgm->magic_number[1] == '2'){
		if ( *magic_Number != MAGIC_NUMBER_ASCII_PGM){ 

		/* failed magic number check   */
		/* be tidy: close the file       */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", fname);
        
		/* and return                    */
		return EXIT_BAD_MAGIC_NUMBER;

		} /* failed magic number check   */	
	}
	else if(pgm->magic_number[1] == '5'){
		if ( *magic_Number != MAGIC_NUMBER_RAW_PGM){ 

		/* failed magic number check   */
		/* be tidy: close the file       */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", fname);
        
		/* and return                    */
		return EXIT_BAD_MAGIC_NUMBER;
		}
	}
	else{
		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", fname);
        
		/* and return                    */
		return EXIT_BAD_MAGIC_NUMBER;
	}
	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");

	/* check for a comment line              */
	char nextChar = fgetc(inputFile);
	if (nextChar == '#'){ 
	/* comment line                */
		/* allocate buffer               */
		pgm->commentLine = (char *)malloc(MAX_COMMENT_LINE_LENGTH + 2);

		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(pgm->commentLine, MAX_COMMENT_LINE_LENGTH + 2, inputFile);

		/* NULL means failure            */
		if (commentString == NULL || strlen(commentString) > MAX_COMMENT_LINE_LENGTH)

			{ /* NULL comment read   */
			/* free memory           */
			free(pgm->commentLine);
			/* close file            */
			fclose(inputFile);

			/* print an error message */
			printf("ERROR: Bad Comment Line (%s)", fname);
		
			/* and return            */
			return BAD_COMMENT_LINE ;

			} /* NULL comment read   */
		} /* comment line */
	else
		{ /* not a comment line */
		/* put character back            */
		ungetc(nextChar, inputFile);

		} /* not a comment line */

	/* read in width, height, grays          */
	/* whitespace to skip blanks             */
	scanCount = fscanf(inputFile, " %u %u %u", &(pgm->width), &(pgm->height), &(pgm->maxGray));

	/* sanity checks on size & grays         */
	/* must read exactly three values        */
	if 	(
		(scanCount != 3				)	||
		(pgm->width < MIN_IMAGE_DIMENSION	) 	||
		(pgm->width >= MAX_IMAGE_DIMENSION	) 	||
		(pgm->height < MIN_IMAGE_DIMENSION	) 	||
		(pgm->height >= MAX_IMAGE_DIMENSION	))
		{ /* failed size sanity check    */
		/* free up the memory            */
		free(pgm->commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Dimensions (%s)\n", fname);
		
		/* and return                    */
		return BAD_DIMENSION;

	} /* failed size sanity check    */
	if(pgm->maxGray	!= 255	){

		/* free up the memory            */
		free(pgm->commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Max Gray Value (%s)", fname);
		return 6;
	}
	/* allocate the data pointer             */
	pgm->imageData = (unsigned char**)malloc(pgm->height * sizeof(*pgm->imageData));
	for (int i = 0; i < pgm->height; i++)
	{
		pgm->imageData[i] = (unsigned char *) malloc (pgm->width * sizeof(unsigned char));
		if (pgm->imageData[i] == NULL)
		{ /* malloc failed */
		/* free up memory                */
		free(pgm->commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Image Malloc Failed (%s)\n", fname);	
		
		/* return error code             */
		return IMAGE_MALLOC_FAILED; 
		} /* malloc failed */
	}

	/* allocate the space for the element*/
	/* sanity check for memory allocation    */


	/* pointer for efficient read code       */
	if(pgm->magic_number[1] == '2'){
		int grayValue = -1;
		for (int i = 0; i < pgm->height; i++)
		{
			for (int j = 0; j < pgm->width; j++)
			{
				grayValue = -1;
				int scanCount = fscanf(inputFile, " %u", &grayValue);

				/* sanity check	                 */
				if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))

					{ /* fscanf failed */
					/* free memory           */
					free(pgm->commentLine);
					free(pgm->imageData);	

					/* close file            */
					fclose(inputFile);

					/* print error message   */
					printf("ERROR: Bad Data (%s)\n", fname);	
				
					/* and return            */
					return BAD_DATA;
					} /* fscanf failed */

				/* set the pixel value           */
				pgm->imageData[i][j] = (unsigned char) grayValue;
			}
		}

		/* per gray value */
		/* read next value               */
		
		/* per gray value */
		int checkdata = fscanf(inputFile, "%u", &grayValue);
		if(checkdata == 1){
			printf("ERROR: Bad Data (%s)", fname);
			return BAD_DATA;
		}	
	}
	else if (pgm->magic_number[1] == '5'){
		int grayValue = -1;
		fgetc(inputFile);
		for (int i = 0; i < pgm->height; i++)
		{
			for (int j = 0; j < pgm->width; j++)
			{
				grayValue = -1;
				int scancount = fread(&grayValue, sizeof(unsigned char), 1, inputFile);
				if(scancount != 1){
					printf("ERROR: Bad Data (%s)", fname);
					return BAD_DATA; 
				}
				pgm->imageData[i][j] = (unsigned char) grayValue; 
			}
		}
		int checkdata = fscanf(inputFile, "%u", &grayValue);
		if(checkdata == 1){
			printf("ERROR: Bad Data (%s)", fname);
			return BAD_DATA;
		}
	}
	else{
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", fname);
        
		/* and return                    */
		return EXIT_BAD_MAGIC_NUMBER;

		} /* failed magic number check   */
	/* we're done with the file, so close it */
	fclose(inputFile);
	return EXIT_NO_ERRORS; 
}

int Writefunction(PGMStructure *pgm, const char *fname){
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
	size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n",pgm->magic_number[1], pgm->width, pgm->height, pgm->maxGray);

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
			for (int j = 0; j < pgm->width; j++)
			{
				/* per gray value */
				/* get next char's column        */
				int nextCol = (j+1) % pgm->width;

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
		}
	}
	else if(pgm->magic_number[1] == '5'){
		for (int i = 0; i < pgm->height; i++)
		{
			for (int j = 0; j < pgm->width; j++)
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
	else{
		fclose(outputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", fname);
        
		/* and return                    */
		return EXIT_BAD_MAGIC_NUMBER;
		 /* failed magic number check   */
	}
	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
} /* main() */
	