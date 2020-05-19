#include "Final.h"
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
		struct math* tmp = tree->right;
		destroy_tree(tree->left);
		tree = assig(tree, tree->right);
		free(tmp);
		return tree;
	}

	if ((tree->data == (double) '-' || tree->data == (double) '+') && (tree->right->data == 0 && tree->right->type == NUMB))
	{
		destroy_tree(tree->right);
		struct math* tmp = tree->left;
		tree = assig(tree, tree->left);
		free(tmp);
		return tree;
	}

	if ((tree->data == (double) '*') && (tree->right->data == 0 && tree->right->type == NUMB))
	{
		tree->left = destroy_tree(tree->left);
		struct math* tmp = tree->right;
		tree = assig(tree, tree->right);
		free(tmp);
		return tree;
	}

	if ((tree->data == (double) '*' || tree->data == (double) '/') && (tree->left->data == 0 && tree->left->type == NUMB))
	{
		tree->right = destroy_tree(tree->right);
		struct math* tmp = tree->left;
		tree = assig(tree, tree->left);
		free(tmp);
		return tree;
	}

	if ((tree->data == (double) '*') && (tree->left->data == 1 && tree->left->type == NUMB))
	{
		destroy_tree(tree->left);
		struct math* tmp = tree->right;
		tree = assig(tree, tree->right);
		free(tmp);
		return tree;
	}

	if ((tree->data == (double) '/' || tree->data == (double) '*') && (tree->right->data == 1 && tree->right->type == NUMB))
	{
		destroy_tree(tree->right);
		struct math* tmp = tree->left;
		tree = assig(tree, tree->left);
		free(tmp);
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