#pragma once
#include "check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMB 12
#define SIGN 14
#define OK 21
#define CONST_AND_VAR 15
#define IT_IS_VAR 18
#define IT_IS_NUMB 19

#define ERROR 134
#define BUFSIZE 200
#define STRSIZE 400
#define PLUS 89
#define MINUS 67


enum prior{
	NUM,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

enum TRIG{
	ARCSIN,
	ARCCOS,
	ARCTG,
	ARCCTG,
	SIN,
	COS,
	TG,
	CTG
};




struct math
{
	double data;
	struct math* left;
	struct math* right;
	int type;
	int prior;
};



int print_tree(struct math* tree, FILE* log);
int usual_print(struct math* tree, FILE* log);
struct math* cpy(struct math* tree, struct math* newtree, FILE* log);
struct math* assig(struct math* ftree, struct math* stree);
struct math* destroy_tree(struct math* tree);
int create_graph(struct math* tree, FILE* f, FILE* log);
struct math* add_node(struct math* tree, double value, int typeval, FILE* log);
struct math* create_tree(struct math* tree, char* name, FILE* log);




