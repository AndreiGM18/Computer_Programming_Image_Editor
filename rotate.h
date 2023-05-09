// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef ROTATE_H
#define ROTATE_H

#include <stdio.h>

#include "image.h"

double ***alloc_reverse_copy(image_t image);

void rot_90_square(image_t *image);

void rot_square(image_t *image, int angle);

void rot_90_full(image_t *image);

void rot_full(image_t *image, int angle);

void rotate_command(image_t *image, int load_fail, char *tok);

#endif
