#pragma once
#include "Tree.h"
#include "Derivate.h"
#include "check.h"

struct math* create_logar(struct math* tree, struct math* buf_tree, FILE* log);
struct math* der_log(struct math* tree, struct math* der_tree, FILE* log);
struct math* der_any_log(struct math* tree, struct math* der_tree, FILE* log);
struct math* der_any_pow(struct math* tree, struct math* der_tree, FILE* log);
struct math* der_pow(struct math* tree, struct math* der_tree, FILE* log);

int print_logarithm(struct math* tree, FILE* log);

