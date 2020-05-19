#include "Logarithms_and_pow.h"


struct math* der_log(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_log, NULL, log)
	
	der_tree = add_node(der_tree, (double) '*', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left = add_node(der_tree->left, (double) '/', SIGN, log);
	CHECKRES(der_tree->left, NULL, add_node, log, NULL)

	der_tree->right = derivative(tree->right, der_tree->right, log);
	CHECKRES(der_tree->right, NULL, derivative in der_log, log, NULL)

	der_tree->left->left = add_node(der_tree->left->left, 1, NUMB, log);
	CHECKRES(der_tree->left->left, NULL, add_node, log, NULL)

	der_tree->left->right = cpy(tree->right, der_tree->left->right, log);
	CHECKRES(der_tree->left->right, NULL, cpy, log, NULL)

	return der_tree;
}


struct math* der_any_log(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_any_log, NULL, log)

	if (tree->left->data == (double) 'e' && tree->left->type == CONST_AND_VAR)
	{
		der_tree = der_log(tree, der_tree, log);
		CHECKRES(der_tree, NULL, der_log, log, NULL)
		return der_tree;
	}

	struct math* buf_tree = create_logar(tree->right, buf_tree, log);
	CHECKRES(buf_tree, NULL, create_logar, log, NULL)

	struct math* another_buf_tree = create_logar(tree->left, another_buf_tree, log);
	CHECKRES(another_buf_tree, NULL, create_logar, log, NULL)

	tree->left = buf_tree;
	tree->right = another_buf_tree;

	tree->data = (double) '/';
	tree->prior = THIRD;

	der_tree = derivative(tree, der_tree, log);
	CHECKRES(der_tree, NULL, derivative in der_any_log, log, NULL)

	return der_tree;
}

struct math* create_logar(struct math* tree, struct math* buf_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, create_logar, NULL, log)

	buf_tree = add_node(buf_tree, (double) 'l', SIGN, log);
	CHECKRES(buf_tree, NULL, add_node, log, NULL)

	buf_tree->left = add_node(buf_tree, (double) 'e', CONST_AND_VAR, log);

	buf_tree->right = tree, buf_tree->right;

	return buf_tree;
}

struct math* der_pow(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_plus_minus, NULL, log)
	
	der_tree = add_node(der_tree, (double) '*', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left = cpy(tree, der_tree->left, log);
	CHECKRES(der_tree->left, NULL, cpy, log, NULL)

	der_tree->right = derivative(tree->right, der_tree->right, log);
	CHECKRES(der_tree->right, NULL, derivative, log, NULL)		

	return der_tree;
}

struct math* der_any_pow(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_plus_minus, NULL, log)

	if (tree->left->data == 'e' && tree->left->type == CONST_AND_VAR)
	{
		der_tree = der_pow(tree, der_tree, log);
		CHECKRES(der_tree, NULL, der_pow, log, NULL)

		return der_tree;
	}

	struct math* buf_tree = add_node(buf_tree, (double) '*', SIGN, log);
	CHECKRES(buf_tree, NULL, add_node, log, NULL)	

	buf_tree->left = add_node(buf_tree->left, (double) 'l', SIGN, log);
	CHECKRES(buf_tree->left, NULL, add_node, log, NULL)

	buf_tree->left->left = add_node(buf_tree->left->left, (double) 'e', CONST_AND_VAR, log);
	CHECKRES(buf_tree->left->left, NULL, add_node, log, NULL)

	buf_tree->left->right = tree->left;



	buf_tree->right = tree->right;

	tree->right = buf_tree;

	tree->left = add_node(buf_tree->left->left, (double) 'e', CONST_AND_VAR, log);

	der_tree = der_pow(tree, der_tree, log);
	CHECKRES(der_tree, NULL, der_pow, log, NULL)

	return der_tree;
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