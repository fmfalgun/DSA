//
// Given a string input from the user,
// print every unique character and how many times it appears,
// sorted by frequency (highest first).
//

#include <stdio.h>
#include <stdlib.h>

void main(void){

	// dynamic string input used google and geminie for syntx overview
	int capacity = 10;
	int length = 0;
	char *str = malloc(capacity * sizeof(char));
	int ch;

	if (!str) return;

	printf("Enter String\n");
	
	while ((ch = getchar()) != '\n' && ch != EOF){
		if (length + 1 >= capacity){
			capacity *= 2;
			char *temp = realloc(str, capacity * sizeof(char));
			if (!temp){
				free(str);
				return;
			}
			str = temp;
		}
		str[length++] = (char)ch;
	}
	str[length++] = '\0';
	// scanning values in string. Using there ascii value and 
	// storing them in freq array of string where each number represent 
	// specific letter. approach learned from querying this message at google
	// "how to use hash table to take record of letters in string in C"

	int freq[256] = {-1};
	
	for (int i = 0; str[i] != '\0'; i++){
		freq[(unsigned char)str[i]]++;
	}

	//printing charcters and there count
	int non_zero_index[256] = {-1}, counter=0;
	for (int i = 0; i < 256; i++){
		if (freq[i] > 0){
			//printf("%c: %d\n", i, freq[i]);
			non_zero_index[counter] = i;
			counter++;
		}
	}	
	non_zero_index[counter] = -1;

	// sorting
	for (int i = 0; i < counter; i++){
		for (int j = i+1; j < counter; j++){
			if (freq[non_zero_index[i]] < freq[non_zero_index[j]]){
				int temp = non_zero_index[i];
				non_zero_index[i] = non_zero_index[j];
				non_zero_index[j] = temp;
			}
		}
	}

	//printing characters and there count in decreasing order
	for (int i = 0; i < 256; i++){
		if (non_zero_index[i] != -1){
			printf("--> %c: %d\n", non_zero_index[i], freq[non_zero_index[i]]);
		}
		else break;
	}

}
