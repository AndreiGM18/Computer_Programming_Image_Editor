// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef APPLY_H
#define APPLY_H

#include <stdio.h>
#include "image.h"

double ***alloc_copy(image_t image);

void edge(image_t *image);

void sharpen(image_t *image);

void blur(image_t *image);

void gaussian_blur(image_t *image);

void apply_command(image_t *image, int load_fail, char *tok);

#endif
