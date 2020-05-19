#include "Final.h"

struct math* assig(struct math* ftree, struct math* stree)
{
	ftree->data = stree->data;
	ftree->type = stree->type;
	ftree->prior = stree->prior;
	ftree->left = stree->left;
	ftree->right = stree->right;
	return ftree;
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
	else
		newtree->left = NULL;
	if (tree->right)
	{
		newtree->right = cpy(tree->right, newtree->right, log);
		CHECKRES(newtree->right, NULL, cpy, log, NULL)
	}
	else
		newtree->right = NULL;

	return newtree;
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



struct math* destroy_tree(struct math* tree)
{
	if (tree == NULL)
		return tree;

	if (tree->left)
		tree->left = destroy_tree(tree->left);
	if (tree->right)
		tree->left = destroy_tree(tree->right);


	free(tree);
	return tree = NULL;
}

int create_graph(struct math* tree, FILE* f, FILE* log)
{
	CHECK_LOG(log, ERROR)

	CHECK_NULL_ARG(tree, create_graph, ERROR, log)
	CHECK_NULL_ARG(f, create_graph, ERROR, log)
	

	int res1 = 0, res2 = 0;
	if (tree->left != NULL)
	{
		fprintf(f, "\t%.2lf->%.2lf\n", tree->data, tree->left->data);
		res1 = create_graph(tree->left, f, log);
	}


	if (tree->right != NULL)
	{
		fprintf(f, "\t%.2lf->%.2lf\n", tree->data, tree->right->data);
		res2 = create_graph(tree->right, f, log);
	}


	return res1 + res2;
}


struct math* add_node(struct math* tree, double value, int typeval, FILE* log)
{ 
	CHECK_LOG(log, NULL)
	tree = (struct math*) calloc (1, sizeof(struct math));
	CHECKRES(tree, NULL, add_node, log, NULL)

	tree->data = value;
	tree->type = typeval;

	if ((value == (double) '+') || (value == (double) '-'))
		tree->prior = FIFTH;
	else if ((value == (double) '*') || (value == (double) '/'))
		tree->prior = FOURTH;

	else if (value == (double) '^')
		tree->prior = THIRD;

	else if (value == (double) 'l')
		tree->prior = SECOND;

	else if (value == (double) 't')
		tree->prior = FIRST;

	else
		tree->prior = NUM;

	tree->left = NULL;
	tree->right = NULL;

	return tree;
}


struct math* create_tree(struct math* tree, char* name, FILE* log) 
{
	CHECK_NULL_ARG(name, create_tree, NULL, log);
	CHECK_LOG(log, NULL);


	FILE* fdata = fopen(name, "r");

	char* rightrec = change_record(fdata, log);
	CHECKRES(rightrec, NULL, change_record, log, NULL)


	fclose(fdata);


	tree = read_str(rightrec, tree, log);

	return tree;
}
