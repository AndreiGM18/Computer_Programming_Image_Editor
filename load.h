// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>

#include "image.h"

void skip(void);

void skip_comments(FILE *fin);

void read(image_t *image, FILE *filename);

void get_types(image_t *image, char *type);

void load_command(image_t *image, int *load_fail, char *tok);

#endif
