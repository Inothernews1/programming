#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

//If we are compiling on windows, compile these functions
#ifdef _WIN32
#include <string.h>

//Declare a buffer for user of size 2048
static char buffer[2048];

//Fake realine function
char* readline(char* prompt) {
	//Puts prompt to stdout
	fputs(prompt, stdout);
	//Reads line from stdin and stores it in buffer
	//Stops when 2048 chars or a newline char is read
	fgets(buffer, 2048, stdin);
	//Declare string cpy, allocate it's length to be the length of the buffer
	//plus a null char and return a pointer to it
	char* cpy = malloc(strlen(buffer) + 1);
	//Copies buffer to cpy
	strcpy(cpy, buffer);
	//Appends NUL terminator
	cpy[strlen(cpy) - 1] = '\0';
	return cpy;
}

//Fake add_history function
void add_history(char* unused) {}

//Otherwise include the editline headers

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

//use operator string to see which operation to perform
long eval_op(long x, char* op, long y) {
	if (strcmp(op, "+") == 0) { return x + y; }
	if (strcmp(op, "-") == 0) { return x - y; }
	if (strcmp(op, "*") == 0) { return x * y; }
	if (strcmp(op, "/") == 0) { return x / y; }
	return 0;
}

long eval(mpc_ast_t* t) {
	//If tagged as number return it directly
	if(strstr(t->tag, "number")) {
		//Convert the string to a long
		return atoi(t->contents);
	}

	//The operator is always the second child
	char* op = t->children[1]->contents;
	//We store the third child in 'x'
	long x = eval(t->children[2]);

	//Iterate the remaining children and combining
	int i = 3;
	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		i++;
	}

	return x;
}

int main(int argc, char** argv) {
	//Create the parsers
	mpc_parser_t* Number		= mpc_new("number");
	mpc_parser_t* Operator	= mpc_new("operator");
	mpc_parser_t* Expr			= mpc_new("expr");
	mpc_parser_t* LispC			= mpc_new("lispc");

	//Define them with the following parameters
	mpca_lang(MPCA_LANG_DEFAULT,
		"	number		:	/-?[0-9]+/ ;															\
			operator	: '+' | '-' | '*' | '/' ; 									\
			expr			:	<number> | '(' <operator> <expr>+ ')' ; 	\
			lispc			:	/^/ <operator> <expr>+ /$/ ;							\
		",
		Number, Operator, Expr, LispC);

	//Print Verion and Exit Info
	puts("LispC Ver 0.0.0.0.2");
	puts("Press Ctrl+C to Exit\n");

	//Never ending loop
	while(1) {
		//Output our prompt and get input
		char* input = readline("LispC> ");

		//Add input to history
		add_history(input);

		//Attempt to parse the user input
		mpc_result_t r;

		//Call mpc_parse with parser LispC and the input string input
		//Copies result of parse into r and returns 1 on success and 0 on failure
		//Use address of operator & on r when we pass it into the function
		if(mpc_parse("<stdin>", input, LispC, &r)) {
			long result = eval(r.output);
			printf("%li\n", result);
			mpc_ast_delete(r.output);
		} else {
			//On failure the error is copied into r in the field error
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		//Free retrieved input
		free(input);
	}

	//Undefine and delete our parsers
	mpc_cleanup(4, Number, Operator, Expr, LispC);
	return 0;
}
