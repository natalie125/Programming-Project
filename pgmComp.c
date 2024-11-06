/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "pgmReadWrite.h"

#include "convertpgm.h"

int main(int argc, char **argv){
	/* main */
	int err = 0;

	/* allocate the memory for file 1 */
	PGMStructure *pgmstc1 = malloc(sizeof(PGMStructure));
	Structure(pgmstc1);

	/* allocate the memory for file 2 */
	PGMStructure *pgmstc2 = malloc(sizeof(PGMStructure));
	Structure(pgmstc2);

	/* check the number of arguments which is correct */
	if(argc == 1){

		/* check if argument is 0*/
		/* return special message indicating the correct usage and return 0*/
		printf("Usage: %s inputImage.pgm inputImage.pgm", argv[0]); 

		/* return no error*/
		return EXIT_NO_ERRORS; 
	}
	else if (argc != 3){ 
        /* wrong arg count */
		/* print an error message        */
        printf("ERROR: Bad Argument Count");

        /* and return an error code      */
        return EXIT_WRONG_ARG_COUNT;
	}
/* use the checkerror to see if read function for file 1 return error */
    err = ReadFunction(pgmstc1 ,argv[1]);
    if(err != 0)
        return err; 

    /*   then go to read file function to check if they have any error for file 2*/
    err = ReadFunction(pgmstc2 ,argv[2]);
    if(err != 0)
        return err; 

    /* compare function */
    if(pgmstc1->magic_number[1] == pgmstc2->magic_number[2]){
        for (int i = 0; i < pgmstc1->height; i++){ 
            for (int j = 0; j < pgmstc1->width; j++){ 
                if(pgmstc1->imageData[i][j] != pgmstc2->imageData[i][j]){
                    printf("DIFFERENT");
                    return EXIT_NO_ERRORS;
                }
            }
        }
        /* compare everything in the pgm structure */
        if((pgmstc1->commentLine != pgmstc2->commentLine) || 
            (pgmstc1->width != pgmstc2->width) ||  
            (pgmstc1->height != pgmstc2->height) ||  
            (pgmstc1->maxGray != pgmstc2->maxGray)){

            /* print different and return 0 */
            printf("DIFFERENT");
            return EXIT_NO_ERRORS; 
        }   
        else{
            /* else they are identical and return 0 */
            printf("IDENTICAL");
            return EXIT_NO_ERRORS;
        } 
    }
    else if(pgmstc1->magic_number[1] != pgmstc2->magic_number[2] &&pgmstc1->magic_number[1] == '2'){
        err = pgma2b(pgmstc1, argv[1]);
        if(err != 0)
            return err;
    }
    else{
        err = pgmb2a(pgmstc1, argv[1]);
        if(err != 0)
            return err; 
    }
    for (int i = 0; i < pgmstc1->height; i++){ 
        for (int j = 0; j < pgmstc1->width; j++){ 
            if(pgmstc1->imageData[i][j] != pgmstc2->imageData[i][j]){
                printf("DIFFERENT");
                return EXIT_NO_ERRORS;
            }
        }
    }
    /* compare everything in the pgm structure */
    if((pgmstc1->commentLine != pgmstc2->commentLine) || 
        (pgmstc1->width != pgmstc2->width) ||  
        (pgmstc1->height != pgmstc2->height) ||  
        (pgmstc1->maxGray != pgmstc2->maxGray)){
        
        /* print different and return 0 */
        printf("DIFFERENT");
        return EXIT_NO_ERRORS; 
    }   
    else{
        /* else they are identical and return 0 */
        printf("IDENTICAL");
        return EXIT_NO_ERRORS;
    } 
}