#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define CHARACTERS 40
#define WORDS 10

void alloc2DimArr(char*** array){ // 40x10 array
	*array=malloc(WORDS*sizeof(char*)); //10 strings)
	for(int i=0;i<WORDS;i++){
		(*array)[i]=malloc(CHARACTERS*sizeof(char)); //40 chars/string)
	}
}

void free2DimArr(char** array){
	for(int i=0; i<WORDS; i++)
		free(array[i]);
	free(array);
}

void print_arr(char **string_arr) {
	for(int w = 0; w < WORDS; w++) { //printout of the char array content
		for(int c = 0; c < CHARACTERS; c++) {
			printf("%c", string_arr[w][c]);
		}
		printf("\n");
	}
}

void put_char_arr_to_0 (char **string_arr) {
	for(int w = 0; w < WORDS; w++) { //puts the char array to "\0"
		for(int c = 0; c < CHARACTERS; c++) {
			string_arr[w][c] = '\0';
		}
	}
}

int main(int argc, char *argv[]) {
	char** string_arr = NULL; //creates 2D array - pointer
	alloc2DimArr(&string_arr); //allocates memory
	
	bool flag = false;
	if (argc < 2 || argc >3) {
		printf("call: ./program_name filename(including_commands) -e(optionally)\n");
	}
	if (argc == 3) {
		flag = true;
		printf(flag ? "flag: true\n" : "flag: false\n");
	}
	
	printf("\ncontent of argv:\n");	
	for (int i = 0; i < argc; i++) {
		puts(argv[i]);
	}	
	
	FILE *fileptr;

	if ((fileptr = fopen(argv[1], "r")) == NULL){
		printf("ERROR: fopen\n");
		exit (EXIT_FAILURE);
	}
	
	printf("\ncontent of %s:\n", argv[1]);
	char stream_char;
	int characters = 0;
	int words = 0;
	
	while((stream_char = fgetc (fileptr)) != EOF) {
		string_arr[words][characters] = stream_char;
//		printf("char: %c\n", string_arr[words][characters]);
		characters++;

		if(stream_char == '\n') {
			if(string_arr[0][0] == '#' || string_arr[0][0] == '\n' || string_arr[0][0] == '\0') {
				printf("leere zeile oder kommentar (\\n or # or \\0)\n");
				put_char_arr_to_0(string_arr);
				continue;
			}
			printf("\ninhalt nullzeiger: %s", string_arr[0]);
			printf("\ninhalt nullzeiger: %s", string_arr[1]);
			printf("\ninhalt nullzeiger: %s", string_arr[2]);
			printf("\ninhalt nullzeiger: %s\n", string_arr[3]);
				
			string_arr[++words] = NULL;
//			int exe = execvp(string_arr[0], string_arr);	
//			printf("execvp: %d\n", exe);
			printf("words: %d\t characters: %d\n", words+1, characters+1);	

			print_arr(string_arr);
			
			put_char_arr_to_0(string_arr);
			
			characters = 0;
			words = 0;
		} 
		if (stream_char == 32) { // 32 = space
			printf("words: %d\t characters: %d\n", words+1, characters+1);	
			words++;			
			characters = 0;
		}
	}
	
	free2DimArr(string_arr);
	if (fclose(fileptr) != 0){
			printf("ERROR: fclose\n");
	}
	return EXIT_SUCCESS;
}
