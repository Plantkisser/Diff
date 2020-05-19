#pragma once
#include "Tree.h"
#include "Derivate.h"
#include "check.h"

struct math* der_plus_minus(struct math* tree, struct math* der_tree, FILE* log);
struct math* der_mul(struct math* tree, struct math* der_tree, int sign, FILE* log);
struct math* der_div(struct math* tree, struct math* der_tree, FILE* log);
struct math* minus(struct math* tree, FILE* log);