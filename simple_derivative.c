struct math* der_plus_minus(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_plus_minus, NULL, log)
	
	der_tree = add_node(der_tree, tree->data, SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left = derivative(tree->left, der_tree->left, log);
	CHECKRES(der_tree->left, NULL, derivative, log, NULL)

	der_tree->right = derivative(tree->right, der_tree->right, log);
	CHECKRES(der_tree->right, NULL, derivative, log, NULL)

	return der_tree;
}

struct math* der_mul(struct math* tree, struct math* der_tree, int sign, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_mul, NULL, log)

	if (sign == PLUS)
	{	
		der_tree = add_node(der_tree, (double) '+', SIGN, log);
		CHECKRES(der_tree, NULL, add_node, log, NULL)
	}
	else 
	{
		der_tree = add_node(der_tree, (double) '-', SIGN, log);
		CHECKRES(der_tree, NULL, add_node, log, NULL)	
	}
	der_tree->left = add_node(der_tree, (double) '*', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left->left = derivative(tree->left, der_tree->left->left, log);
	CHECKRES(der_tree->left->left, NULL, derivative, log, NULL)

	der_tree->left->right = cpy(tree->right, der_tree->left->right, log);
	CHECKRES(der_tree->left->right, NULL, cpy, log, NULL)



	der_tree->right = add_node(der_tree, (double) '*', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->right->left = derivative(tree->right, der_tree->right->left, log);
	CHECKRES(der_tree->right->left, NULL, derivative, log, NULL)

	der_tree->right->right = tree->left;

	return der_tree;	
}


struct math* der_div(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_div, NULL, log)

	der_tree = add_node(der_tree, (double) '/', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->right = add_node(der_tree->right, (double) '^', SIGN, log);
	CHECKRES(der_tree->right, NULL, add_node, log, NULL)

	der_tree->right->left = cpy(tree->right, der_tree->right->left, log);
	CHECKRES(der_tree->right->left, NULL, cpy, log, NULL)

	der_tree->right->right = add_node(der_tree->right->right, 2, NUMB, log);
	CHECKRES(der_tree->right->right, NULL, add_node, log, NULL)

	der_tree->left = der_mul(tree, der_tree->left, MINUS, log);
	CHECKRES(der_tree->left, NULL, add_node, log, NULL)

	return der_tree;
}