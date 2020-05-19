#include <stdio.h>
#include <stdlib.h>
#include <string.h>






#include "Final.h"




# define CREATELOG(name);\
{\
	name = fopen(#name"log.txt", "a");\
	if (!name)\
	{\
		printf("Cannot create log\n");\
		return ERROR;\
	}\
}












int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Wrong arguments\n");
		return 0;
	}


	struct math* tree = NULL;

	FILE* diff = NULL;
	CREATELOG(diff)

	tree = create_tree(tree, argv[1],diff);
	CHECKRES(tree, 0, create_tree, diff, NULL)


	struct math* der_tree = derivative(tree, der_tree, diff);

	der_tree = optimize(der_tree, diff);

	int res = print_tree(der_tree, diff);
	CHECKRES(res, 0, print_tree, diff, ERROR)
	
	
	tree = destroy_tree(tree);
	der_tree = destroy_tree(der_tree);

	fclose(diff);

	return 0;
}












