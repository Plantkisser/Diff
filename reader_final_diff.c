#define NUMB 12
#define SIGN 14
#define OK 21
#define CONST_AND_VAR 15
#define IT_IS_VAR 18
#define IT_IS_NUMB 19


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

char* change_record(FILE* fdata, FILE* log);

struct math* read_str(char* str, struct math* tree, FILE* log);

int clean_str(char* str, int size, FILE* log);

char* delete_brackets (char* str, FILE* log);

struct math* add_node(struct math* tree, double value, int typeval, FILE* log);

int isnum(char* str, FILE* log);

char* choose_ptr(char* str, char oper1, char oper2, FILE* log);

struct math* destroy_tree(struct math* tree);

int create_graph(struct math* tree, FILE* f, FILE* log);

int check_logarithm(char* str, char* newstr, int* ipb, int* i, FILE* log);

int record_with_brackets(char* str, char* newstr, int* ipb, int* i, FILE* log);

int is_extra(char* str, FILE* log);

int check_trig(char* str, char* newstr, int* ipb, int* i, FILE* log);




struct math* create_tree(struct math* tree, FILE* log) 
{
	CHECK_LOG(log, NULL);


	FILE* fdata = fopen("input.txt", "r");

	char* rightrec = change_record(fdata, log);
	CHECKRES(rightrec, NULL, change_record, log, NULL)


	fclose(fdata);


	tree = read_str(rightrec, tree, log);

	return tree;
}



char* change_record(FILE* fdata, FILE* log) 
{
	CHECK_LOG(log, NULL)

	CHECK_NULL_ARG(fdata, change_record, NULL, log)

	fseek(fdata, 0, SEEK_END);
	int size = ftell(fdata);
	rewind(fdata);


	char* buf =(char*) calloc(size, sizeof(char));
	CHECKNULL(buf, 0, log)
	


	char* str = (char*) calloc(size + 1, sizeof(char));
	CHECKNULL(str, 0, log)


	fread(str, sizeof(char), size, fdata);



	int i = 0;
	int ipb = 0;
	while(str[i] != '\0')
	{
		if (!isspace(str[i]))
		{
			if (str[i] == 'l')
			{
				int res = check_logarithm(str, buf, &ipb, &i, log);
				CHECKRES(res, NULL, check_logarithm, log, ERROR)
			}
			else
			{
				int res = check_trig(str, buf, &ipb, &i, log);
				CHECKRES(res, NULL, check_trig, log, ERROR)

				if (res == 0)
				{
					buf[ipb] = str[i];
					ipb++;
				}
			}
		}
		i++;
	}
	free(str);
	buf[ipb] = '\0';
	return buf;
}


struct math* read_str(char* str, struct math* tree, FILE* log)
{
	CHECK_LOG(log, NULL)


	//printf("%s\n", str);
	CHECK_NULL_ARG(str, read_str, NULL, log)


	str = delete_brackets(str, log); //1
	CHECKRES(str, NULL, read_str, log, NULL);


	if (isnum(str, log) == IT_IS_NUMB) //3
	{
		tree = add_node(tree, atof(str), NUMB, log); //2
		CHECKRES(tree, NULL, read_str, log, NULL)


		return tree;
	}

	if (isnum(str, log) == IT_IS_VAR)
	{
		tree = add_node(tree, str[0], CONST_AND_VAR, log);
		CHECKRES(tree, NULL, read_str, log, NULL)

		return tree;
	}


	char* ptr = choose_ptr(str, '+', '-', log); //4
	if (!ptr)
	{
		ptr = choose_ptr(str, '*', '/', log);
		if (!ptr)
		{
			ptr = choose_ptr(str, '^', '\0', log);
			if (!ptr)
			{
				ptr = choose_ptr(str, 'l', '\0', log);	
				if (!ptr)
					ptr = choose_ptr(str, 't', '\0', log);
			}
		}
	}
	
	if (!ptr)
	{
		printf("Error read log\n");
		fprintf(log, "There is a problem in read_str cannot read %s\n", str);
		return NULL;
	}


	char* buf = (char*) calloc (BUFSIZE, sizeof(char));
	CHECKNULL(buf, NULL, log)


	//printf("%d\n", *ptr);

	tree = add_node(tree, (int) *ptr, SIGN, log);
	CHECKRES(tree, NULL, read_str, log, NULL)


	int res = mystrcpy(buf, str, ptr, log);
	CHECKRES(res, NULL, read_str, log, ERROR)


	tree->left = read_str(buf, tree->left, log);

	res = clean_str(buf, BUFSIZE, log);
	CHECKRES(res, NULL, read_str, log, ERROR)

	res = mystrcpy(buf, ptr, NULL, log);
	CHECKRES(res, NULL, read_str, log, ERROR)	

	tree->right = read_str(buf + 1, tree->right, log);
	return tree;

}



int mystrcpy (char* buf, char* str, char* end, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(str, mystrcpy, ERROR, log)
	CHECK_NULL_ARG(buf, mystrcpy, ERROR, log)
	int ipbuf = 0;
	if (!end)
	{
		while(str[ipbuf] != '\0')
		{
			buf[ipbuf] = str[ipbuf];
			ipbuf++;
		}
		return 0;
	}
	while(str + ipbuf < end)
	{
		buf[ipbuf] = str[ipbuf];
		ipbuf++;
	}
	buf[ipbuf] = '\0';
	return 0;
}





int clean_str(char* str, int size, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(str, clean_str, ERROR, log)

	for (int i = 0; i < size; i++)
		str[i] = 0;
	return 0;
}



char* delete_brackets (char* str, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(str, NULL, delete_brackets, log)

	int fl_brack = is_extra(str, log);
	CHECKRES(fl_brack, NULL, is_exra, log, ERROR)

	if (fl_brack != 0)
	{
		str++;
		str[strlen(str) - 1] = '\0';
	}
	return str;
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




int isnum(char* str, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(str, isnum, 0, log)
	int  i = 0;

	if (strlen(str) == 1 && (str[0] == 'e' || str[0] == 'x'))
		return IT_IS_VAR;

	for (i = 0; str[i] != '\0'; i++)
		if (!isdigit(str[i])) ////add
			return 0;
	return IT_IS_NUMB;
}




char* choose_ptr(char* str, char oper1, char oper2, FILE* log)
{
	CHECK_LOG(log, NULL)
	CHECK_NULL_ARG(str, choose_ptr, NULL, log)
	int  i = strlen(str) - 1;
	int mode = 0;
	while((((str[i] != oper1) && (str[i] != oper2)) || (mode > 0)) && i > 0)
		{
			if (str[i] == ')')
				mode++;
			if (str[i] == '(')
				mode--;
			i--;
		}

	if (i == 0)
		return NULL;

	return str + i;
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




int check_logarithm(char* str, char* newstr, int* ipb, int* i, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(str, check_logarithm, ERROR, log)
	CHECK_NULL_ARG(newstr, check_logarithm, ERROR, log)
	CHECK_NULL_ARG(ipb, check_logarithm, ERROR, log)
	CHECK_NULL_ARG(i, check_logarithm, ERROR, log)


	while(isalpha(str[*i]))
		++*i;

	int res = record_with_brackets(str, newstr, ipb, i, log);
	CHECKRES(res, ERROR, check_logarithm, log, ERROR)

	newstr[*ipb] = 'l';
	++*ipb;

	res = record_with_brackets(str, newstr, ipb, i, log);
	CHECKRES(res, ERROR, check_logarithm, log, ERROR)

	return 0;
}




int record_with_brackets(char* str, char* newstr, int* ipb, int* i, FILE* log)
{
	CHECK_LOG(log, ERROR)
	if (str[*i] != '(')
	{
		fprintf(log, "wrong record of function\n");
		return ERROR;
	}

	while(str[*i] != ')')
	{
		newstr[*ipb] = str[*i];
		++*ipb;
		++*i;
	}

	newstr[*ipb] = str[*i];

	++*i;
	++*ipb;
	return 0;
}




int is_extra(char* str, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(str, is_extra, ERROR, log)

	if(str[0] == '(' && str[strlen(str) - 1] == ')')
	{
		int i = 0;
		int count_br = 0;
		for (i = 1; str[i + 1] != '\0'; i++)
		{
			if (str[i] == '(')
				count_br++;
			if (str[i] == ')')
				count_br--;
			if (count_br < 0)
				return 0;
		}
		return 1;
	}
	else return 0;
}


int check_trig(char* str, char* newstr, int* ip, int* i, FILE* log)
{
	CHECK_LOG(log, ERROR)
	CHECK_NULL_ARG(str, check_logarithm, ERROR, log)
	CHECK_NULL_ARG(newstr, check_logarithm, ERROR, log)
	CHECK_NULL_ARG(ip, check_logarithm, ERROR, log)
	CHECK_NULL_ARG(i, check_logarithm, ERROR, log)



	#define SEARCH_TRIG_FUNC(str, func, VAL)                     \
		if (strstr(str + *i, func) == str + *i)                  \
		{                                                        \
			newstr[*ip] = '(';                                   \
			++*ip;                                               \
                                                                 \
			newstr[*ip] = '0' + VAL;                             \
			++*ip;                                               \
                                                                 \
			newstr[*ip] = ')';                                   \
			++*ip;                                               \
                                                                 \
			newstr[*ip] = 't';                                   \
			++*ip;                                               \
                                                                 \
			*i = *i + strlen(func);                              \
                                                                 \
			int res = record_with_brackets(str, newstr, ip, i, log); \
			CHECKRES(res, ERROR, check_trig, log, ERROR)         \
                                                                 \
			return OK;                                           \
		}                                                        \

	SEARCH_TRIG_FUNC(str, "arcsin", ARCSIN)

	SEARCH_TRIG_FUNC(str, "arccos", ARCCOS)

	SEARCH_TRIG_FUNC(str, "arctg" , ARCTG)

	SEARCH_TRIG_FUNC(str, "sin", SIN)

	SEARCH_TRIG_FUNC(str, "cos", COS)

	SEARCH_TRIG_FUNC(str, "tg", TG)

	SEARCH_TRIG_FUNC(str, "arcctg", ARCCTG)

	SEARCH_TRIG_FUNC(str, "ctg", CTG)

	return 0;

	#undef SEARCH_TRIG_FUNC
}







