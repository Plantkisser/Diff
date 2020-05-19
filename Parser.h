#pragma once



#include "check.h"
#include "Tree.h"
#include "ctype.h"



char* change_record(FILE* fdata, FILE* log); // change "log" -> "l" 

struct math* read_str(char* str, struct math* tree, FILE* log);

char* delete_brackets (char* str, FILE* log);

int isnum(char* str, FILE* log);

char* choose_ptr(char* str, char oper1, char oper2, FILE* log);

int mystrcpy (char* buf, char* str, char* end, FILE* log);

int check_logarithm(char* str, char* newstr, int* ipb, int* i, FILE* log);

int record_with_brackets(char* str, char* newstr, int* ipb, int* i, FILE* log);

int is_extra(char* str, FILE* log);

int check_trig(char* str, char* newstr, int* ipb, int* i, FILE* log);