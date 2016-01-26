#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpc.h"

// If we are compiling on windows, compile these functions
#ifdef _WIN32
#include <string.h>

// Declare a buffer for user of size 2048
static char buffer[2048];

// Fake realine function
char* readline(char* prompt) {
	// Puts prompt to stdout
	fputs(prompt, stdout);
	// Reads line from stdin and stores it in buffer
	// Stops when 2048 chars or a newline char is read
	fgets(buffer, 2048, stdin);
	// Declare string cpy, allocate it's possible length to be the length of the buffer
	// plus a null char and return a pointer to it
	char* cpy = malloc(strlen(buffer) + 1);
	// Copies buffer to cpy
	strcpy(cpy, buffer);
	// Appends NUL terminator
	cpy[strlen(cpy) - 1] = '\0';
	return cpy;
}

// Fake add_history function
void add_history(char* unused) {}

// Otherwise include the editline headers

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

// Create enum of possible error types
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

// Create enum of possible lval types
enum { LVAL_NUM, LVAL_ERR };

// Declare new lval struct
typedef struct {
	int type;
	long num;
	int err;
} lval;

// Create a new number type lval
lval lval_num (long x) {
	lval v;
	v.type = LVAL_NUM;
	v.num = x;

	return v;
}

// Create a new error type lval
lval lval_err (int x) {
	lval v;
	v.type = LVAL_ERR;
	v.err = x;

	return v;
}

// Print an lval
void lval_print (lval v) {
	switch (v.type) {
		// In the case the type is a number print it, then break out of the switch
		case LVAL_NUM:
			printf("%li\n", v.num);
			break;

		// In the case the type is an error
		case LVAL_ERR:
			if (v.err == LERR_DIV_ZERO) {
				printf("ERROR: Division By Zero!");
			}

			if (v.err == LERR_BAD_OP) {
				printf("ERROR: Invalid Operator!");
			}

			if (v.err == LERR_BAD_NUM) {
				printf("ERROR: Invalid Number!");
			}

			break;
	}

}

// Print an lval followed by a newline
void lval_println (lval v) {
	lval_print(v);
	putchar('\n');
}

// Use operator string to see which operation to perform
lval eval_op(lval x, char* op, lval y) {
	// If either value is an error return it
	if (x.type == LVAL_ERR) { return x; }
	if (x.type == LVAL_ERR) { return x; }

	// Otherwise do math on the number values
	if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
	if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
	if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
	if (strcmp(op, "/") == 0) {
		return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num / y.num);
	}
	if (strcmp(op, "%") == 0) { return lval_num(x.num % y.num); }
	if (strcmp(op, "^") == 0) { return lval_num(pow(x.num, y.num)); }

	return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t* t) {
	// If whatever is sent is a number, catch it
	if(strstr(t->tag, "number")) {
		// Check if there is some error in conversion
		errno = 0;
		long x = strtol(t->contents, NULL, 10);
		return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_OP);
	}

	// The first child is a label e.g. '(' or beginning label
	// The second child is always an operator, so we store that into op
	char* op = t->children[1]->contents;
	// We evaluate whatever the third child is and store it in 'x'
	lval x = eval(t->children[2]);

	// Continue to evaluate until none are left
	int i = 3;
	// While the child's tag is expr
	while (strstr(t->children[i]->tag, "expr")) {
		// Evaluate the remaining children and perform the operation with 'x'
		x = eval_op(x, op, eval(t->children[i]));
		i++;
	}

	return x;
}

int main(int argc, char** argv) {
	// Create the parsers
	mpc_parser_t* Number		= mpc_new("number");
	mpc_parser_t* Operator	= mpc_new("operator");
	mpc_parser_t* Expr			= mpc_new("expr");
	mpc_parser_t* LispC			= mpc_new("lispc");

	// Define them with the following parameters
	mpca_lang(MPCA_LANG_DEFAULT,
		"	number		:	/-?[0-9]+/ ;																							\
			operator	: '+' | '-' | '*' | '/' | '^' | '%' ; 			\
			expr			:	<number> | '(' <operator> <expr>+ ')' ; 									\
			lispc			:	/^/ <operator> <expr>+ /$/ ;															\
		",
		Number, Operator, Expr, LispC);

	// Print Verion and Exit Info
	puts("LispC Ver 0.0.0.0.5");
	puts("Press Ctrl+C to Exit\n");

	// Never ending loop
	while(1) {
		// Output our prompt and get input
		char* input = readline("LispC> ");

		// Add input to history
		add_history(input);

		// Attempt to parse the user input
		mpc_result_t r;

		// Call mpc_parse with parser LispC and the input string input
		// Copies result of parse into r and returns 1 on success and 0 on failure
		// Use address of operator & on r when we pass it into the function
		if(mpc_parse("<stdin>", input, LispC, &r)) {
			lval result = eval(r.output);
			lval_println(result);
			mpc_ast_delete(r.output);
		} else {
			// On failure the error is copied into r in the field error
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		// Free retrieved input
		free(input);
	}

	// Undefine and delete our parsers
	mpc_cleanup(4, Number, Operator, Expr, LispC);
	return 0;
}
