// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>

#include "image.h"

double clamp(double x);

void swap_values(int *a, int *b);

void swap_pointers(double **a, double **b);

int load_fail_message(FILE *f, char *filename, int *load_fail);

int open_fail_message(FILE *fout, char *filename);

void free_image(image_t *image);

#endif
