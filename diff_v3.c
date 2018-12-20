#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 134
#define BUFSIZE 200
#define STRSIZE 400
#define PLUS 89
#define MINUS 67


struct math
{
	double data;
	struct math* left;
	struct math* right;
	int type;
	int prior;
};




#define CREATE_JPG(tree)\
{\
	FILE *fgraph = NULL;\
	fgraph = fopen("tree.dot", "w");\
	fprintf(fgraph, "digraph\n{\n");\
	int res = create_graph(tree, fgraph, diff);\
	if (res != 0) return 0;\
	fprintf(fgraph, "}");\
	fclose(fgraph);\
	system("dot -Tjpg -otree.jpg tree.dot");\
}


# define CREATELOG(name);\
{\
	name = fopen(#name"log.txt", "a");\
	if (!name)\
	{\
		printf("Cannot create log\n");\
		return ERROR;\
	}\
}


#include "check.h"
#include "reader_final_diff.c"



int print_tree(struct math* tree, FILE* log);

int usual_print(struct math* tree, FILE* log);

int print_logarithm(struct math* tree, FILE* log);

struct math* derivative(struct math* tree, struct math* deriv, FILE* log);

struct math* cpy(struct math* tree, struct math* newtree, FILE* log);

struct math* assig(struct math* ftree, struct math* stree);

struct math* optimize(struct math* tree, FILE* log);


#include "simple_derivative.c"
#include "log&pow.c"
#include "der_trig.c"


int main()
{
	struct math* tree = NULL;

	FILE* diff = NULL;
	CREATELOG(diff)

	tree = create_tree(tree, diff);
	CHECKRES(tree, 0, create_tree, diff, NULL)

	CREATE_JPG(tree)

	struct math* der_tree = derivative(tree, der_tree, diff);

	der_tree = optimize(der_tree, diff);

	int res = print_tree(der_tree, diff);
	CHECKRES(res, 0, print_tree, diff, ERROR)
	
	
	tree = destroy_tree(tree);
	der_tree = destroy_tree(der_tree);

	fclose(diff);
	printf("\n");

	return 0;
}


int print_tree(struct math* tree, FILE* log)
{
	if(!tree)
		return 0;

	char* str = calloc(STRSIZE, sizeof(char));
	CHECKNULL(str, ERROR, log)

	char* buf = calloc(STRSIZE, sizeof(char));
	CHECKNULL(str, ERROR, log)


	int res = 0;

	if (tree->data == (double) 'l' && tree->type == SIGN)
		{
			res = print_logarithm(tree, log);
			CHECKRES(res, ERROR, print_tree, log, ERROR)
			return 0;
		}
	if (tree->data == (double) 't' && tree->type == SIGN)
	{
		res = print_trig(tree, log);
		CHECKRES(res, ERROR, print_tree, log, ERROR)
		return 0;
	}

	res = usual_print(tree, log);
	CHECKRES(res, ERROR, print_tree, log, ERROR)


	return 0;
}





int usual_print(struct math* tree, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(tree, usual_print, ERROR, log)

	int res = 0; 

	if (tree->left)
	{
		if (tree->left->prior >= tree->prior)
			printf("(");


		res = print_tree(tree->left, log);
		CHECKRES(res, ERROR, print_tree, log, ERROR)

		if (tree->left->prior >= tree->prior)
			printf(")");
		
	}

	if (tree->type == SIGN)
	{
		int sign = tree->data;
		printf(" %c ", sign);
	}
	else if (tree->type == CONST_AND_VAR)
	{
		int val = tree->data;
		printf("%c", val);
	}
	else
	{
		printf("%.1lf", tree->data);
	}



	if (tree->right)
	{
		if (tree->right->prior >= tree->prior)
			printf("(");

		res = print_tree(tree->right, log);
		CHECKRES(res, ERROR, print_tree, log, ERROR)

		if (tree->right->prior >= tree->prior)
			printf(")");
	}
}



int print_logarithm(struct math* tree, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(tree, print_logarithm, ERROR, log)

	printf("log(");
	
	int res = print_tree(tree->left, log);
	CHECKRES(res, ERROR, print_logarithm, log, ERROR)
	
	printf(")(");

	res = print_tree(tree->right, log);
	CHECKRES(res, ERROR, print_logarithm, log, ERROR)
	
	printf(")");
	return 0;
}




struct math* derivative(struct math* tree, struct math* der_tree, FILE* log)
{
	if (tree->left != NULL)
	{
		switch((int) tree->data)
		{
			case '+':
				der_tree = der_plus_minus(tree, der_tree, log);
				CHECKRES(der_tree, NULL, der_plus_minus, log, NULL)
				break;
			case '-':
				der_tree = der_plus_minus(tree, der_tree, log);
				CHECKRES(der_tree, NULL, der_plus_minus, log, NULL)
				break;
			case '*':
				der_tree = der_mul(tree, der_tree, PLUS, log);
				CHECKRES(der_tree, NULL, der_mul, log, NULL)
				break;
			case '/':
				der_tree = der_div(tree, der_tree, log);
				CHECKRES(der_tree, NULL, der_div, log, NULL)
				break;
			case '^':
				der_tree = der_any_pow(tree, der_tree, log);
				CHECKRES(der_tree, NULL, der_pow, log, NULL)
				break;
			case 'l':
				der_tree = der_any_log(tree, der_tree, log);
				CHECKRES(der_tree, NULL, der_any_log, log, NULL)
				break;
			case 't':
				der_tree = der_any_trig(tree, der_tree, log);
				CHECKRES(der_tree, NULL, der_any_trig, log, NULL)
				break;
			default:
				fprintf(log, "There is a problem in derivative\n");
				return NULL;
		}
		return der_tree;
	}
	else 
	{
		if ((tree->type == NUMB) || (tree->type == CONST_AND_VAR && tree->data != (double) 'x'))
		{
			der_tree = add_node(der_tree, 0, NUMB, log);
			CHECKRES(der_tree, NULL, add_node, log, NULL)
		}
		else
		{
			der_tree = add_node(der_tree, 1, NUMB, log);
			CHECKRES(der_tree, NULL, add_node, log, NULL)
		}
		return der_tree;
	}


}



int print_trig(struct math* tree, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(tree, print_logarithm, ERROR, log)

	switch ((int) tree->left->data)
	{
		case ARCSIN:
			printf("arcsin");
			break;
		case ARCCOS:
			printf("arccos");
			break;
		case ARCTG:
			printf("arctg");
			break;
		case ARCCTG:
			printf("arcctg");
			break;
		case SIN:
			printf("sin");
			break;
		case COS:
			printf("cos");
			break;
		case TG:
			printf("tg");
			break;
		case CTG:
			printf("ctg");
			break;
		default:
			fprintf(log, "there is a problem in print_trig wrong code: %d\n", (int) tree->left->data);
			break;

	}

	printf("(");
	
	int res = print_tree(tree->right, log);
	CHECKRES(res, ERROR, print_logarithm, log, ERROR)
	
	printf(")");

	return 0;	
}


struct math* cpy(struct math* tree, struct math* newtree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, cpy, NULL, log)

	newtree = (struct math*) calloc(1, sizeof(struct math));
	CHECKRES(newtree, NULL, cpy, log, NULL)

	newtree->data = tree->data;
	newtree->type = tree->type;
	newtree->prior = tree->prior;

	if (tree->left)
	{
		newtree->left = cpy(tree->left, newtree->left, log);
		CHECKRES(newtree->left, NULL, cpy, log, NULL)
	}
	if (tree->right)
	{
		newtree->right = cpy(tree->right, newtree->right, log);
		CHECKRES(newtree->right, NULL, cpy, log, NULL)
	}

	return newtree;
}


struct math* optimize(struct math* tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, cpy, NULL, log)

	if (tree->type != SIGN)
		return tree;

	tree->left = optimize(tree->left, log);
	tree->right = optimize(tree->right, log);

	if ((tree->data == (double) '-' || tree->data == (double) '+') && (tree->left->data == 0 && tree->left->type == NUMB))
	{
		tree = assig(tree, tree->right);
		return tree;
	}

	if ((tree->data == (double) '-' || tree->data == (double) '+') && (tree->right->data == 0 && tree->right->type == NUMB))
	{
		tree = assig(tree, tree->left);
		return tree;
	}

	if ((tree->data == (double) '*') && (tree->right->data == 0 && tree->right->type == NUMB))
	{
		tree->left = destroy_tree(tree->left);
		struct math* buf = tree->right;
		tree = assig(tree, buf);
		free(buf);
		return tree;
	}

	if ((tree->data == (double) '*' || tree->data == (double) '/') && (tree->left->data == 0 && tree->left->type == NUMB))
	{
		tree->right = destroy_tree(tree->right);
		struct math* buf = tree->left;
		tree = assig(tree, buf);
		free(buf);
		return tree;
	}

	if ((tree->data == (double) '*') && (tree->left->data == 1 && tree->left->type == NUMB))
	{
		tree = assig(tree, tree->right);
		return tree;
	}

	if ((tree->data == (double) '/' || tree->data == (double) '*') && (tree->right->data == 1 && tree->right->type == NUMB))
	{
		tree = assig(tree, tree->left);
		return tree;
	}

	if ((tree->data == (double) '^') && (tree->right->data == (double) '*' && tree->right->type == SIGN))
		if (tree->right->left->data == 'l' && tree->right->left->type == SIGN)
			if ((tree->right->left->left->data == tree->left->data) && (tree->left->type == tree->right->left->left->type) && (tree->right->left->left->type != SIGN))
			{
				free(tree->left);
				tree->left = tree->right->left->right;
				free(tree->right->left->left);
				free(tree->right->left);

				struct math* buf = tree->right->right;

				free(tree->right);

				tree->right = buf;
			}


	return tree;
}

struct math* assig(struct math* ftree, struct math* stree)
{
	ftree->data = stree->data;
	ftree->type = stree->type;
	ftree->prior = stree->prior;
	ftree->left = stree->left;
	ftree->right = stree->right;
	return ftree;
}
