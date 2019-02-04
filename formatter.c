/*
 * UVic SENG 265, Summer 2018,  A#4
 *
 * This will contain the bulk of the work for the fourth assignment. It
 * provide similar functionality to the class written in Python for
 * assignment #3.
 
	edited by Ronald Liu  V00838627
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"

#define DEFAULT_BUFLEN 80


	int width = 0;				// checking width
	int current_width = 0;		// checking current width
	int left = 0;
	int linespacing = 0;
	int formatting = 0;			// checking if FT is off
	int no_trans = 0;			// checking if no any formatting commands


int FT(char* word){
					
	if (strncmp(word,"off",3)==0){
		formatting = 0;
		return (int)1;
	}
	else if (strncmp(word,"on",2)==0){
		formatting = 1;
		return (int)1;
	}
	return (int)0;
}

void printing(char* word){
	
	if (current_width ==0 && formatting==1 && strncmp(word,"\n",2)!=0){
		if (left>0) {
			int k;
			for (k=0;k<left;k++){
				fprintf(stdout, " ");
				current_width++;
			}
		}
	}
	
	if( (current_width + strlen(word)) > width && formatting==1 ){

		//fprintf(stdout, "[checking]");

		if (linespacing>0){
			fprintf(stdout, "\n");
			int m;
			for (m=0;m<linespacing;m++){
				fprintf(stdout, "\n");
			}
		}else{
			fprintf(stdout, "\n");
		}
		current_width = 0;
		if (left>0) {
			int k;
			for (k=0;k<left;k++){
				fprintf(stdout, " ");
				current_width++;
			}
		}
	}

	
	if( current_width==left ){
		fprintf(stdout, "%s", word);
	}else{
		fprintf(stdout, " %s", word);
	}

	if ( strncmp(word,"—",4)==0 ){
		current_width += (1+1);
		
	}else{
		current_width += (strlen(word)+1);
	}
}

	
void counting(char* word, int *target){
	int object = 0;
	int i;
	for(i = (int)strlen(word)-1;i>=0;i--){
				
		int x = word[i] - '0';
		int y = x;

		if ( (x >= 0)&&(x <= 9) ){
				int j;
				for(j=0; j<((int)strlen(word)-1-i); j++){
				
					y = x*10;
				}
			object += y;
		}
	}
	*target = object;
}

void counting2(char* word, int *target){
	int object = 0;
	int i;
	for(i = (int)strlen(word)-1;i>=1;i--){
				
		int x = word[i] - '0';
		int y = x;

		if ( (x >= 0)&&(x <= 9) ){
				int j;
				for(j=0; j<((int)strlen(word)-1-i); j++){
				
					y = x*10;
				}
			object += y;
		}
	}
	
	if ( left + object > 20){
		*target = 20;
	}else{
		*target = left + object;
	}
}

void counting3(char* word, int *target){
	int object = 0;
	int i;
	for(i = (int)strlen(word)-1;i>=1;i--){
				
		int x = word[i] - '0';
		int y = x;

		if ( (x >= 0)&&(x <= 9) ){
				int j;
				for(j=0; j<((int)strlen(word)-1-i); j++){
				
					y = x*10;
				}
			object += y;
		}
	}
	
	if ( left < object ){
		*target = 0;
	}else{
		*target = left - object;
	}
}

int checking(char* word){
	
	if ( word[0] > 0 ){
		
		int y = word[0] - '0';

		if ( (y >= 0)&&(y <= 9) ){
			return (int)1;
		}
		else{
			return (int)0;
		}
	}
	return (int)1;
}



char **format_file(FILE *infile) {
	
	//char* line = NULL;
	//unsigned int length = 0;
	//int curr_max = 0;
	
	
	unsigned int len_max = sizeof(char);
    unsigned int current_size = 0;
    
	char *del = " ";
	
    char *buffer = malloc(len_max);
    current_size = len_max;


    if(buffer != NULL)
    {
		int c = 0;
		unsigned int i =0;
		int first_space_line = 0;
		int first_word = 0;
		int special = 0;	

		while ( c != EOF ) {
			
			i = 0;
			first_word = 0;
			special = 0;
			
				
			while (( c = getc(infile) ) != '\n' && c != EOF)
			{
				buffer[i++]=(char)c;

				if(i == current_size)
				{
					current_size = i+len_max;
					buffer = realloc(buffer, current_size);
				}
			}
			

			
			if ( (char)c != EOF && first_space_line == 0 && i == 0 && (char)c == '\n' ){
				
				if (linespacing>0){
					//fprintf(stdout, "!\n");
					int m;
					for (m=0;m<linespacing-1;m++){
						fprintf(stdout, "\n");
					}
				}
				
				fprintf(stdout, "\n");
				fprintf(stdout, "\n");
				first_space_line = 1;
				current_width = 0;
				
				if (linespacing>0){
					fprintf(stdout, "\n");
					int m;
					for (m=0;m<linespacing;m++){
						fprintf(stdout, "\n");
					}
				}
			}
			else 
			if ( (char)c != EOF && first_space_line == 1 && i == 0 && (char)c == '\n' ){
				fprintf(stdout, "\n");
				current_width = 0;
				
				if (linespacing>0){
					fprintf(stdout, "\n");
					int m;
					for (m=0;m<linespacing;m++){
						fprintf(stdout, "\n");
					}
				}
			}
			
			if ( (char)c == EOF && formatting == 1 && first_space_line == 0 ) {		// checking space line for last line
				fprintf(stdout, "\n");
			}		


			
			//buffer[i++] = '\n';
			buffer[i] = '\0';
			
			
			//fprintf(stdout,"***%s***", buffer);	
			
			char tmp[i];	
			char copy[i];
			strncpy(copy, buffer, i+1);
			
			char* word = strtok(buffer, del);
			
			
			while(word != NULL)
			{
				//fprintf(stdout, "%s ", word);
				//word = strtok(NULL, del);
				
				/*
				if (current_width ==0 && formatting==1 && strncmp(word,"\n",2)!=0){
					if (left>0) {
						int k;
						for (k=0;k<left;k++){
							fprintf(stdout, " ");
							current_width++;
						}
					}
				}
				*/
				
				if (strncmp(word,".LW",3)==0){
					
					no_trans = 1;
					strncpy(tmp, word, i);
					word = strtok(NULL, del);
					
					if ( checking(word) == 1 ){
					
						formatting = 1;
						counting(word, &width);
						word = strtok(NULL, del);
					}
					else{
						if ( formatting == 1){
							printing(tmp);
							printing(word);
							word = strtok(NULL, del);
						}
					}
				}
				else
				
				if (strncmp(word,".LM",3)==0){
					
					no_trans = 1;
					strncpy(tmp, word, i);
					word = strtok(NULL, del);
					
					if ( checking(word) == 1 ){
					
						counting(word, &left);
						word = strtok(NULL, del);
					}
					else if ( word[0] == '+' && checking(&word[1]) == 1 ){
						
						formatting = 1;
						counting2(word, &left);
						word = strtok(NULL, del);
						
						
						
						

					}
					else if ( word[0] == '-' && checking(&word[1]) == 1 ){
						
						formatting = 1;
						counting3(word, &left);
						word = strtok(NULL, del);
					}
					else{
						
						if ( formatting == 1){
							printing(tmp);
							printing(word);
							word = strtok(NULL, del);
						}
					}
				}
				else
					
				if (strncmp(word,".LS",3)==0){

					no_trans = 1;
					strncpy(tmp, word, i);
					word = strtok(NULL, del);
					
					if ( checking(word) == 1 ){
					
						counting(word, &linespacing);
						word = strtok(NULL, del);
						
					}else{
						
						if ( formatting == 1){
							printing(tmp);
							printing(word);
							word = strtok(NULL, del);
						}
					}
				}
				else

				if (strncmp(word,".FT",3)==0 && first_word == 0){
					
					no_trans = 1;
					strncpy(tmp, word, i);
					word = strtok(NULL, del);
					

					if ( FT(word) == 1 && formatting == 0 ) {    // formatting off
						
						//printf("*******************");
						char *del2 = "\n";
						word = strtok(NULL, del2);
						special = 1;
						
					}else 
					if ( FT(word) == 1 && formatting == 1 ){	// formatting on
						word = strtok(NULL, del);
					}
					else{
						printing(tmp);
						printing(word);
						word = strtok(NULL, del);
					}
				}
				else 
				if ( no_trans==1 && word != NULL && formatting ==1 ){

						printing(word);
						word = strtok(NULL, del);
						first_word = 1;
						first_space_line = 0;
				}
				else
				if ( special == 1 ) {			// when .FT off print the rest of the line
					printing(word);
					word = strtok(NULL, del);
				}
				else{
					word = strtok(NULL, del);
					first_word = 1;
				}
			}
			
			
			// for cases when without any formatting command
			if ( no_trans == 0 && strlen(copy) != 0 && i > 0){
				fprintf(stdout,"%s\n", copy);
			}
			
			
			// for cases when have FT off
			if ( no_trans == 1 && strlen(copy) != 0  && formatting==0 && special == 0 ){
				
				fprintf(stdout,"%s\n", copy);
				//printf("*******************");
			}
			

		
		//printf("print end");
		
		}
		
		free(buffer);
		buffer = NULL;
		
    }

	exit(0);
	return NULL;
}


char **format_lines(char **lines, int num_lines) {
	
	char **result = NULL;
	//result[0] = NULL;
/*	
	int test = sizeof(char*);
	printf("size: %d", test);
	
	printf("error\n");
	//printf("\n*******************%s\n", result);
	
	result = (char **)malloc(sizeof(char *));
	result[0] = (char *)malloc(sizeof(char)*1000);
	
	
	char **line2;
	for (line2 = result; *line2 != NULL; line2++) {
		printf ("%s\n", *line2);
	}
	
	printf("\n*******************%s\n", result[0]);
	printf("error\n");
	
	result[0] = realloc ( result[0], sizeof(char) * DEFAULT_BUFLEN );
	
	printf("error\n");
	
	if ( result == NULL ){
		
		printf("error\n");
	}
*/	
#ifdef DEBUG
	result = (char **)malloc(sizeof(char *) * 2);
	if (result == NULL) {
		return NULL;
	}

	result[0] = (char *)malloc(sizeof(char) * DEFAULT_BUFLEN);
	if (result[0] == NULL) {
		return NULL;
	}
	strncpy(result[0], "(machine-like voice) STABLE GENIUS!", 
        DEFAULT_BUFLEN-1);

	result[1] = (char *)malloc(sizeof(char) * 2);
	if (result[1] == NULL) {
		return NULL;
	}
	result[1][0] = '\0';
#endif

	char *del = " ";
	//char *copy2 = NULL;
	//char *word = NULL;
	
	//int first_space_line = 0;
	int first_word = 0;
	int special = 0;	
	
	char *buffer = malloc(sizeof(char));
	
	for ( int i = 0; i < num_lines ; i++ ){
		
		//result[i] = lines[i];
		//printf( "%s\n", result[i] );

		int string_length = strlen( lines[i] );
		
		//printf( "*********%d\n", string_length );
		
		buffer = realloc(buffer, string_length*sizeof(char));
		
		strncpy(buffer, lines[i], string_length+1);
		
		
		if (strncmp(buffer,"\n",2)==0){
			printf( "\n" );
		}
		
		
		
		char tmp[string_length];	
		char copy[string_length];
		strncpy(copy, buffer, string_length+1);
	
		char* word = strtok(buffer, del);
		
		//printf( "testing**************%s\n", word);

		
		while(word != NULL)
			{			
				if (strncmp(word,".LW",3)==0){
					
					no_trans = 1;
					strncpy(tmp, word, i);
					word = strtok(NULL, del);
					
					if ( checking(word) == 1 ){
					
						formatting = 1;
						counting(word, &width);
						word = strtok(NULL, del);
					}
					else{
						if ( formatting == 1){
							printing(tmp);
							printing(word);
							word = strtok(NULL, del);
						}
					}
				}
				else
				
				if (strncmp(word,".LM",3)==0){
					
					no_trans = 1;
					strncpy(tmp, word, i);
					word = strtok(NULL, del);
					
					if ( checking(word) == 1 ){
					
						counting(word, &left);
						word = strtok(NULL, del);
					}
					else if ( word[0] == '+' && checking(&word[1]) == 1 ){
						
						formatting = 1;
						counting2(word, &left);
						word = strtok(NULL, del);
						
						
						
						

					}
					else if ( word[0] == '-' && checking(&word[1]) == 1 ){
						
						formatting = 1;
						counting3(word, &left);
						word = strtok(NULL, del);
					}
					else{
						
						if ( formatting == 1){
							printing(tmp);
							printing(word);
							word = strtok(NULL, del);
						}
					}
				}
				else
					
				if (strncmp(word,".LS",3)==0){

					no_trans = 1;
					strncpy(tmp, word, i);
					word = strtok(NULL, del);
					
					if ( checking(word) == 1 ){
					
						counting(word, &linespacing);
						word = strtok(NULL, del);
						
					}else{
						
						if ( formatting == 1){
							printing(tmp);
							printing(word);
							word = strtok(NULL, del);
						}
					}
				}
				else

				if (strncmp(word,".FT",3)==0 && first_word == 0){
					
					no_trans = 1;
					strncpy(tmp, word, i);
					word = strtok(NULL, del);
					

					if ( FT(word) == 1 && formatting == 0 ) {    // formatting off
						
						//printf("*******************");
						char *del2 = "\n";
						word = strtok(NULL, del2);
						special = 1;
						
					}else 
					if ( FT(word) == 1 && formatting == 1 ){	// formatting on
						word = strtok(NULL, del);
					}
					else{
						printing(tmp);
						printing(word);
						word = strtok(NULL, del);
					}
				}
				else 
				if ( no_trans==1 && word != NULL && formatting ==1 ){

						printing(word);
						strcat( result[0], word );
						//printf("\n*******************%s\n", result[0]);
						word = strtok(NULL, del);
						first_word = 1;
						//first_space_line = 0;
				}
				else
				if ( special == 1 ) {			// when .FT off print the rest of the line
					printing(word);
					word = strtok(NULL, del);
				}
				else{
					word = strtok(NULL, del);
					first_word = 1;
				}
			}
		// for cases when without any formatting command
		if ( no_trans == 0 && strlen(copy) != 0 && i > 0){
			fprintf(stdout,"%s\n", copy);
		}
			
		
		// for cases when have FT off
		if ( no_trans == 1 && strlen(copy) != 0  && formatting==0 && special == 0 ){
			
			fprintf(stdout,"%s\n", copy);
			//printf("*******************");
		}
	
	}
	
	fprintf(stdout,"\n");
	free(buffer);
	
	char **line;
	
	for (line = result; *line != NULL; line++) {
		//printf ("%s\n", *line);
	}
	
	exit(0);
	
	return result;   // result
}
