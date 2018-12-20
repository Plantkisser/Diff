struct math* der_arcsin(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_arccos(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_arctg(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_arcctg(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_ctg(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_tg(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_cos(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_sin(struct math* tree, struct math* der_tree, FILE* log);

struct math* minus(struct math* tree, FILE* log);

struct math* der_any_trig(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_any_trig, NULL, log)

	switch ((int) tree->left->data)
	{
		case ARCSIN:
			der_tree = der_arcsin(tree, der_tree, log);
			CHECKRES(der_tree, NULL, der_arcsin, log, NULL)
			break;
		case ARCCOS:
			der_tree = der_arccos(tree, der_tree, log);
			CHECKRES(der_tree, NULL, der_arccos, log, NULL)
			break;
		case ARCTG:
			der_tree = der_arctg(tree, der_tree, log);
			CHECKRES(der_tree, NULL, der_arctg, log, NULL)
			break;
		case ARCCTG:
			der_tree = der_arcctg(tree, der_tree, log);
			CHECKRES(der_tree, NULL, der_arcctg, log, NULL)
			break;
		case SIN:
			der_tree = der_sin(tree, der_tree, log);
			CHECKRES(der_tree, NULL, der_sin, log, NULL)
			break;
		case COS:
			der_tree = minus(der_tree, log);
			CHECKRES(der_tree, NULL, minus, log, NULL)

			der_tree->right = der_cos(tree, der_tree, log);
			CHECKRES(der_tree, NULL, der_cos, log, NULL)
			break;
		case TG:
			der_tree = der_tg(tree, der_tree, log);
			CHECKRES(der_tree, NULL, der_tg, log, NULL)
			break;
		case CTG:
			der_tree = minus(der_tree, log);
			CHECKRES(der_tree, NULL, minus, log, NULL)

			der_tree = der_ctg(tree, der_tree, log);
			CHECKRES(der_tree, NULL, der_ctg, log, NULL)
			break;
		default:
			fprintf(log, "Wrong type of trig function %d\n", tree->left->data);
	}
}


struct math* minus(struct math* tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	
	tree = add_node(tree, (double) '-', SIGN, log);
	CHECKRES(tree, add_node, NULL, log, NULL)
	
	tree->left = add_node(tree->left, 0, NUMB, log);
	CHECKRES(tree->left, add_node, NULL, log, NULL)

	return tree;
}


struct math* der_arcsin(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_arsin, NULL, log)

	der_tree = add_node(der_tree, (double) '*', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left = add_node(der_tree->left, (double) '/', SIGN, log);
	CHECKRES(der_tree->left, NULL, add_node, log, NULL)

	der_tree->left->left = add_node(der_tree->left->left, 1, NUMB, log);
	CHECKRES(der_tree->left->left, NULL, add_node, log, NULL)

	der_tree->left->right = add_node(der_tree->left->right, (double) '^', SIGN, log);
	CHECKRES(der_tree->left->right, NULL, add_node, log, NULL)

	der_tree->left->right->right = add_node(der_tree->left->right->right, (double) '/', SIGN, log);
	CHECKRES(der_tree->left->right->right, NULL, add_node, log, NULL)

	der_tree->left->right->right->right = add_node(der_tree->left->right->right->right, 2, NUMB, log);
	CHECKRES(der_tree->left->right->right->right, NULL, add_node, log, NULL)

	der_tree->left->right->right->left = add_node(der_tree->left->right->right->left, 1, NUMB, log);
	CHECKRES(der_tree->left->right->right->left, NULL, add_node, log, NULL)

	der_tree->left->right->left = add_node(der_tree->left->right->left,(double) '-', SIGN, log);
	CHECKRES(der_tree->left->right->left, NULL, add_node, log, NULL)

	der_tree->left->right->left->right = add_node(der_tree->left->right->left->right, (double) '^', SIGN, log);
	CHECKRES(der_tree->left->right->left->right, NULL, add_node, log, NULL)

	der_tree->left->right->left->left = add_node(der_tree->left->right->left->left, 1, NUMB, log);
	CHECKRES(der_tree->left->right->left->left, NULL, add_node, log, NULL)

	der_tree->left->right->left->right->right = add_node(der_tree->left->right->left->right->right, 2, NUMB, log);
	CHECKRES(der_tree->left->right->left->right->right, NULL, add_node, log, NULL)

	der_tree->left->right->left->right->left = cpy(tree->right, der_tree->left->right->left->right->left, log);
	CHECKRES(der_tree->left->right->left->right->left, NULL, cpy, log, NULL)

	der_tree->right = derivative(tree->right, der_tree->right, log);
	CHECKRES(der_tree->right, NULL, derivative, log, NULL)

	return der_tree;	

}

struct math* der_arccos(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_arccos, NULL, log)

	der_tree = add_node(der_tree, (double) '-', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left = add_node(der_tree->left, 0, NUMB, log);
	CHECKRES(der_tree->left, NULL, add_node, log, NULL)

	der_tree->right = der_arcsin(tree, der_tree->right, log);
	CHECKRES(der_tree->right, NULL, der_arcsin, log, NULL)

	return der_tree;
}

struct math* der_arctg(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_arctg, NULL, log)

	der_tree = add_node(der_tree, (double) '/', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->right = add_node(der_tree->right, (double) '+', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->right->left = add_node(der_tree->right->left, 1, NUMB, log);
	CHECKRES(der_tree->right->left, NULL, add_node, log, NULL)

	der_tree->right->right = add_node(der_tree->right->right, (double) '^', SIGN, log);
	CHECKRES(der_tree->right->right, NULL, add_node, log, NULL)

	der_tree->right->right->left = cpy(tree->right, der_tree->right->right->left, log);
	CHECKRES(der_tree->right->right->left, NULL, cpy, log, NULL)

	der_tree->right->right->right = add_node(der_tree->right->right->right, 2, NUMB, log);
	CHECKRES(der_tree->right->right->right, NULL, add_node, log, NULL)

	der_tree->left = derivative(tree->right, der_tree, log);
	CHECKRES(der_tree->left, NULL, derivative, log, NULL)

	return der_tree;
}

struct math* der_arcctg(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_arcctg, NULL, log)

	der_tree = add_node(der_tree, (double) '-', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left = add_node(der_tree->left, 0, NUMB, log);
	CHECKRES(der_tree->left, NULL, add_node, log, NULL)

	der_tree->right = der_arctg(tree, der_tree->right, log);
	CHECKRES(der_tree->right, NULL, der_arctg, log, NULL)

	return der_tree;
}


struct math* der_sin(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_sin, NULL, log)

	der_tree = add_node(der_tree, (double) '*', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left = add_node(der_tree->left, (double) 't', SIGN, log);
	CHECKRES(der_tree->left, NULL, add_node, log, NULL)

	der_tree->left->left = add_node(der_tree->left->left, COS, NUMB, log);
	CHECKRES(der_tree->left->left, NULL, add_node, log, NULL)

	der_tree->left->right = cpy(tree->right, der_tree->left->right, log);
	CHECKRES(der_tree->left->right, NULL, cpy, log, NULL)

	der_tree->right = derivative(tree->right, der_tree->right, log);
	CHECKRES(der_tree->right, NULL, derivative, log, NULL)

	return der_tree;
}

struct math* der_cos(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_cos, NULL, log)

	der_tree = add_node(der_tree, (double) '*', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->left = add_node(der_tree->left, (double) 't', SIGN, log);
	CHECKRES(der_tree->left, NULL, add_node, log, NULL)

	der_tree->left->left = add_node(der_tree->left->left, SIN, NUMB, log);
	CHECKRES(der_tree->left->left, NULL, add_node, log, NULL)

	der_tree->left->right = cpy(tree->right, der_tree->left->right, log);
	CHECKRES(der_tree->left->right, NULL, cpy, log, NULL)

	der_tree->right = derivative(tree->right, der_tree->right, log);
	CHECKRES(der_tree->right, NULL, derivative, log, NULL)

	return der_tree;
}

struct math* der_tg(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_tg, NULL, log)

	der_tree = add_node(der_tree, (double) '/', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->right = add_node(der_tree->right, (double) '^', SIGN, log);
	CHECKRES(der_tree->right, NULL, add_node, log, NULL)

	der_tree->right->right = add_node(der_tree->right->right, 2, NUMB, log);
	CHECKRES(der_tree->right->right, NULL, add_node, log, NULL)

	der_tree->right->left = add_node(der_tree->right->left, 't', SIGN, log);
	CHECKRES(der_tree->right->left, NULL, add_node, log, NULL)

	der_tree->right->left->left = add_node(der_tree->right->right, COS, NUMB, log);
	CHECKRES(der_tree->right->left->left, NULL, add_node, log, NULL)

	der_tree->right->left->right = cpy(tree->right, der_tree->right->left->right, log);
	CHECKRES(der_tree->right->left->right, NULL, cpy, log, NULL)

	der_tree->left = derivative(tree->right, der_tree->right, log);
	CHECKRES(der_tree->left, NULL, cpy, log, NULL)

	return der_tree;
}

struct math* der_ctg(struct math* tree, struct math* der_tree, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(tree, der_ctg, NULL, log)

	der_tree = add_node(der_tree, (double) '/', SIGN, log);
	CHECKRES(der_tree, NULL, add_node, log, NULL)

	der_tree->right = add_node(der_tree->right, (double) '^', SIGN, log);
	CHECKRES(der_tree->right, NULL, add_node, log, NULL)

	der_tree->right->right = add_node(der_tree->right->right, 2, NUMB, log);
	CHECKRES(der_tree->right->right, NULL, add_node, log, NULL)

	der_tree->right->left = add_node(der_tree->right->left, 't', SIGN, log);
	CHECKRES(der_tree->right->left, NULL, add_node, log, NULL)

	der_tree->right->left->left = add_node(der_tree->right->right, SIN, NUMB, log);
	CHECKRES(der_tree->right->left->left, NULL, add_node, log, NULL)

	der_tree->right->left->right = cpy(tree->right, der_tree->right->left->right, log);
	CHECKRES(der_tree->right->left->right, NULL, cpy, log, NULL)

	der_tree->left = derivative(tree->right, der_tree->right, log);
	CHECKRES(der_tree->left, NULL, cpy, log, NULL)

	return der_tree;	
}




















