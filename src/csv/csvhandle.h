/*
 * csvhandle.h
 *
 *  Created on: May 10, 2021
 *      Author: anana
 */

#ifndef CSV_CSVHANDLE_H_
#define CSV_CSVHANDLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int csv_read(int row, int col, char *filename, double **data){
	FILE *file;
	file = fopen(filename, "r");

	int i = 0;
    char line[4098];
	while (fgets(line, 4098, file) && (i < row))
    {
    	// double row[ssParams->nreal + 1];
        char* tmp = strdup(line);

	    int j = 0;
	    const char* tok;
	    for (tok = strtok(line, "\t"); tok && *tok; j++, tok = strtok(NULL, "\t\n"))
	    {
	        data[i][j] = atof(tok);
	        printf("%f\t", data[i][j]);
	    }
	    printf("\n");

        free(tmp);
        i++;
    }
}


#endif /* CSV_CSVHANDLE_H_ */
