// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef SELECT_H
#define SELECT_H

#include <stdio.h>

#include "image.h"

void select_all(image_t *image);

int check_arg_select(char *check);

void continue_select(image_t *image, int new_x1, char *tok);

void select_command(image_t *image, int load_fail, char *tok);

#endif
