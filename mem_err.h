// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef MEM_ERR_H
#define MEM_ERR_H

#include <stdio.h>

#include "image.h"

void mem_err3(double ***p);

void mem_err2(double ***p, int curr_line);

void mem_err1(double ***p, int curr_line, int curr_col);

#endif
