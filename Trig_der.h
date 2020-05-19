#pragma once

#include "Tree.h"
#include "Derivate.h"
#include "check.h"
#include "Simple_der.h"

struct math* der_arcsin(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_arccos(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_arctg(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_arcctg(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_ctg(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_tg(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_cos(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_sin(struct math* tree, struct math* der_tree, FILE* log);

struct math* der_any_trig(struct math* tree, struct math* der_tree, FILE* log);


int print_trig(struct math* tree, FILE* log);
