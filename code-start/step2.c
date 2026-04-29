// Read a text file line by line.
// Count total lines, total words, total characters.
// Print all three. (basically your own wc)

// Use fopen, fgets, fclose. When you're ready.

#include <stdio.h>

void main (void){
	
	FILE *fp = fopen("demo.txt", "r");
	if (fp == NULL) perror("Error opening file");


	char buffer[100];
	int line_counter = 0;
	int word_counter = 0;
	int char_counter = 0;
	bool in_word = false;
	bool buff_limit_reached = false;

	while (fgets(buffer, 100, fp)){
		if (!buff_limit_reached) line_counter ++;
		else buff_limit_reached = false;
		printf("%s", buffer);
		for (int i=0; i<100; i++){
			if ((buffer[i] != ' ' && buffer[i] != '\n') && !in_word){
			       in_word = true;
			       // printf("-->%i\n",in_word);
			       word_counter ++;
			}
			
			if ((buffer[i] == ' ' || buffer[i] == '\n') && in_word){
			       in_word = false;
			       //printf("-->%b\n",in_word);
			}

			if (i == 99) {
				//printf("\n--> %ith buff value = %c \n",i,buffer[i]);
				buff_limit_reached = true;
			}
			if (!buff_limit_reached) char_counter ++;
			if (buffer[i] == '\n') break;
		}
	}

	printf("Number of lines = %i\n", line_counter);
	printf("Number of words = %i\n", word_counter);
	printf("Number of characters = %i\n", char_counter);

	fclose(fp);
	
}
