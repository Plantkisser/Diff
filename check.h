# define CHECKRES(res, ret, name, file, error_value)\
	if (res == error_value)\
	{\
		fprintf(file, "Problem with function " #name  "\n");\
		return ret;\
	}


# define CHECKNULL(ptr, ret, file)\
	if (!ptr)\
	{\
		fprintf(file, "Cannot create" #ptr "\n");\
		return ret;\
	}

#define CHECK_NULL_ARG(name, func, ret, file)\
	if (!name)\
	{\
		fprintf(file, "Nullptr " #name " in function " #func "\n");\
		return ret;\
	}


#define CHECK_LOG(log, ret)\
	if (log == NULL)\
	{\
		printf("Houston we have problem\n akin is a nullptr in change_record\n");\
		return ret;\
	}