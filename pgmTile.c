/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>
#include <string.h>

#include "pgmReadWrite.h"

#include "pgmTile.h"


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
		printf("Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm", argv[0]); 
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
	error = Tilefunction(pgm, atoi(argv[2]), argv[3]);

	/* if read function not equal 0 means there is error, return that */
	if(error != 0)
		return error; 
	/* if no error keep on*/
	/* free the structure*/
	free(pgm); 
	return error; 
}

int Tilefunction(PGMStructure *pgm, int tile_number, const char *fname){
	int width, height, maxGray = 0, count=0;
	char row[10], col[10];
	char * newstr;
	char output[tile_number*tile_number][100];

	PGMStructure pgmList[tile_number*tile_number];

	/*sepeate the width and height by title_nmber*/
	width = (int)pgm->width/tile_number;
	height = (int)pgm->height/tile_number;

	count = 0;
	for(int i = 0; i < tile_number; i++){
		for (int j = 0; j < tile_number; j++){
			maxGray = 0;
			Structure(&pgmList[count]);
			pgmList[count].width = width;
			pgmList[count].height = height;
			pgmList[count].magic_number[0] = pgm->magic_number[0];
			pgmList[count].magic_number[1] = pgm->magic_number[1];

			pgmList[count].imageData = (unsigned char**)malloc(height * sizeof(*pgmList[count].imageData));
			for(int x = i*height; x < i*height + height; x++){
				pgmList[count].imageData[x-i*height] = (unsigned char *) malloc (width * sizeof(unsigned char));
				for(int y = j*width; y < j*width + width; y++){
				
					pgmList[count].imageData[x-i*height][y-j*width] = pgm->imageData[x][y];
					if ((int)(pgm->imageData[x][y]) > maxGray){
						maxGray = (int)(pgm->imageData[x][y]);
					}

				}
			}
			pgmList[count].maxGray = maxGray;

			count++;
		}
	}

	
	for(int i =0; i<tile_number*tile_number;i++){
		for(int x = 0; x<height; x++){
			for(int y = 0; y<width; y++){
				printf(" %u ", pgmList[i].imageData[x][y]);
			}
			printf("\n");
		}
	}
	/*replace the rows and columns*/
	count = 0;
	for(int i = 0; i < tile_number; i++){
		sprintf(row, "%d", i);
		for (int j = 0; j < tile_number; j++){
			sprintf(col, "%d", j);

			newstr = replace(fname, "<row>", row);
			newstr = replace(newstr, "<column>", col);
			// printf("%s\n", newstr);
			strcpy(output[count], newstr);
			printf("%s\n",output[count]);
			Writefunction(&pgmList[count], output[count]);
			count++;
		}
	}
	



	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	return 2;
}

char * replace(char const * const original, char const * const pattern, char const * const replacement) {
  size_t const replen = strlen(replacement);
  size_t const patlen = strlen(pattern);
  size_t const orilen = strlen(original);

  size_t patcnt = 0;
  const char * oriptr;
  const char * patloc;

  // find how many times the pattern occurs in the original string
  for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
  {
    patcnt++;
  }

  {
    // allocate memory for the new string
    size_t const retlen = orilen + patcnt * (replen - patlen);
    char * const returned = (char *) malloc( sizeof(char) * (retlen + 1) );

    if (returned != NULL)
    {
      // copy the original string, 
      // replacing all the instances of the pattern
      char * retptr = returned;
      for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
      {
        size_t const skplen = patloc - oriptr;
        // copy the section until the occurence of the pattern
        strncpy(retptr, oriptr, skplen);
        retptr += skplen;
        // copy the replacement 
        strncpy(retptr, replacement, replen);
        retptr += replen;
      }
      // copy the rest of the string.
      strcpy(retptr, oriptr);
    }
    return returned;
  }
}
