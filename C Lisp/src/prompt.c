#include <stdio.h>

//Declare a buffer for user input of size 2048
static char input[2048];

int main(int argc, char** argv) {

	//Print Verion and Exit Info
	puts("LispC Ver 0.0.0.0.1");
	puts("Press Ctrl+C to Exit\n");

	//Never ending loop
	while(1) {

		//Output our prompt
		fputs("LispC> ", stdout);

		//Read a line of user input of max size 2048
		fgets(input, 2048, stdin);

		//Echo input back to user
		printf("No you're a %s", input);
	}

	return 0;
}
