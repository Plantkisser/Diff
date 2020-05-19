#pragma once
#include "Tree.h"




struct math* derivative(struct math* tree, struct math* deriv, FILE* log);
struct math* optimize(struct math* tree, FILE* log);