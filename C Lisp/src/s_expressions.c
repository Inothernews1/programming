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

// Create enum of possible lval types
enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR };

// Declare new lval struct
typedef struct lval {
	int type;
	long num;
	// Error and Symbol types have some string data
	char* err;
	char* sym;
	// Count and pointer to a list of lval*
	int count;
	struct lval** cell;
} lval;

// Construct a pointer to a new number lval
lval* lval_num (long x) {
	lval* v = malloc(sizeof(lval));
	v->type = LVAL_NUM;
	v->num = x;

	return v;
}

// Construct a pointer to a new error lval
lval* lval_err (char* m) {
	lval* v = malloc(sizeof(lval));
	v->type = LVAL_ERR;
	v->err = malloc(strlen(m) + 1);
	strcpy(v->err, m);

	return v;
}

// Construct a pointer to a new symbol lval
lval* lval_sym (char* s) {
	lval* v = malloc(sizeof(lval));
	v->type = LVAL_SYM;
	v->sym = malloc(strlen(s) + 1);
	strcpy(v->sym, s);

	return v;
}

void lval_del (lval* v) {
	switch (v->type) {
		// Do nothing special for number type
		case LVAL_NUM: break;

		// For err or sym free the string data
		case LVAL_ERR: free(v->err); break;
		case LVAL_SYM: free(v->sym); break;

		// If sexpr then delete all elements inside
		case LVAL_SEXPR:
			for (int i = 0; i < v->count; i++) {
				lval_del(v->cell[i]);
			}

			// Also free the memory allocated to contain the pointers
			free(v->cell);
		break;
	}

	// Free the memory allocated for the lval struct itself
	free(v);
}

lval* lval_pop (lval* v, int i) {
	// Find the item at i
	lval* x = v->cell[i];

	// Shift memory after the item at i over the top
	memmove(&v->cell[i], &v->cell[i+1], sizeof(lval*) * (v->count - i - 1));

	// Decrease the count of items in the list
	v->count--;

	// Reallocate the memory used
	v->cell = realloc(v->cell, sizeof(lval*) * v->count);

	return x;
}

lval* lval_take(lval* v, int i) {
	lval* x = lval_pop(v, i);
	lval_del(v);

	return x;
}

lval* builtin_op (lval* a, char* op) {
	// Ensure all arguments are numbers
	for (int i = 0; i < a->count; i++) {
		if (a->cell[i]->type != LVAL_NUM) {
			lval_del(a);
			return lval_err("Cannot operate on non-number!");
		}

	}

	// Pop the first element
	lval* x = lval_pop(a, 0);

	// If no arguments and sub then preform unary negation
	if ((strcmp(op, "-") == 0) && a->count == 0) {
		x->num = -x->num;
	}

	// While there are still elements remaining
	while (a->count > 0) {
		// Pop the next element
		lval* y = lval_pop(a, 0);

		if (strcmp(op, "+") == 0) { x->num += y->num; }
		if (strcmp(op, "-") == 0) { x->num -= y->num; }
		if (strcmp(op, "*") == 0) { x->num *= y->num; }
		if (strcmp(op, "^") == 0) { x->num = pow(x->num, y->num); }
		if (strcmp(op, "%") == 0) { x->num %= y->num; }
		if (strcmp(op, "/") == 0) {
			if (y->num == 0) {
				lval_del(x);
				lval_del(y);
				x = lval_err("Division by zero!");
				break;
			}

			x->num += y->num;
		}

		lval_del(y);
	}

	lval_del(a);
	return x;
}

lval* lval_eval (lval* v);

lval* lval_eval_sexpr (lval* v) {
	// Evaluate children
	for (int i = 0; i < v->count; i++) {
		v->cell[i] = lval_eval(v->cell[i]);
	}

	// Error checking
	for (int i = 0; i < v->count; i++) {
		if (v->cell[i]->type == LVAL_ERR) { return lval_take(v, i); }
	}

	// Empty expression
	if (v->count == 0) { return v; }

	// Single expression
	if (v->count == 1) { return lval_take(v, 0); }

	// Ensure first element is symbol
	lval* f = lval_pop(v, 0);
	if (f->type != LVAL_SYM) {
		lval_del(f);
		lval_del(v);
		return lval_err("S-Expression does not start with symbol!");
	}

	// Call builtin with operator
	lval* result = builtin_op(v, f->sym);
	lval_del(f);

	return result;
}

lval* lval_eval(lval* v) {
	// Evaluate s-expressions
	if (v->type == LVAL_SEXPR) { return lval_eval_sexpr(v); }
	// All other types remain the same
	return v;
}

// A pointer to a new empty Sexpr lval
lval* lval_sexpr (void) {
	lval* v = malloc(sizeof(lval));
	v->type = LVAL_SEXPR;
	v->count = 0;
	v->cell = NULL;

	return v;
}

lval* lval_read_num (mpc_ast_t* t) {
	errno = 0;
	long x = strtol(t->contents, NULL, 10);
	return errno != ERANGE ? lval_num(x) : lval_err("Invalid number");
}

lval* lval_add (lval* v, lval* x) {
	v->count++;
	v->cell = realloc(v->cell, sizeof(lval*) * v->count);
	v->cell[v->count - 1] = x;
	return v;
}

lval* lval_read (mpc_ast_t* t) {
	// If symbol or number return conversion to that type
	if (strstr(t->tag, "number")) { return lval_read_num(t); }
	if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

	// If root (>) or sexpr then create empty list
	lval* x = NULL;
	if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
	if (strstr(t->tag, "sexpr"))  { x = lval_sexpr(); }

	// Fill this list with any valid expression contained within
	for (int i = 0; i < t->children_num; i++) {
		if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
		if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
		if (strcmp(t->children[i]->contents, "{") == 0) { continue; }
		if (strcmp(t->children[i]->contents, "}") == 0) { continue; }
		if (strcmp(t->children[i]->tag,  "regex") == 0) { continue; }
		x = lval_add(x, lval_read(t->children[i]));
	}

	return x;
}

void lval_print (lval* v);

void lval_expr_print (lval* v, char open, char close) {
	putchar(open);
	for (int i = 0; i < v->count; i++) {
		// Print value contained within
		lval_print(v->cell[i]);

		// Don't print tailing space if last element
		if (i != (v->count - 1)) {
			putchar(' ');
		}

	}

	putchar(close);
}

// Print an lval
void lval_print (lval* v) {
	switch (v->type) {
		case LVAL_NUM:		printf("%li", v->num);					break;
		case LVAL_ERR:		printf("ERROR: %s", v->err);		break;
		case LVAL_SYM:		printf("%s", v->sym);						break;
		case LVAL_SEXPR:	lval_expr_print(v, '(', ')');		break;
	}

}

// Print an lval followed by a newline
void lval_println (lval* v) {
	lval_print(v);
	putchar('\n');
}

int main(int argc, char** argv) {
	// Create the parsers
	mpc_parser_t* Number		= mpc_new("number");
	mpc_parser_t* Symbol		= mpc_new("symbol");
	mpc_parser_t* Sexpr			= mpc_new("sexpr");
	mpc_parser_t* Expr			= mpc_new("expr");
	mpc_parser_t* LispC			= mpc_new("lispc");

	// Define them with the following parameters
	mpca_lang(MPCA_LANG_DEFAULT,
		"	number	:	/-?[0-9]+/ ;														\
			symbol	: '+' | '-' | '*' | '/' | '^' | '%' ; 		\
			sexpr		: '(' <expr>* ')' ;												\
			expr		:	<number> | <symbol> | <sexpr> ; 				\
			lispc		:	/^/ <expr>* /$/ ;												\
		",
		Number, Symbol, Sexpr, Expr, LispC);

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

			lval* x = lval_eval(lval_read(r.output));
			lval_println(x);
			lval_del(x);
		} else {
			// On failure the error is copied into r in the field error
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		// Free retrieved input
		free(input);
	}

	// Undefine and delete our parsers
	mpc_cleanup(5, Number, Symbol, Sexpr, Expr, LispC);
	return 0;
}
