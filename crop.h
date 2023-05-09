// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef CROP_H
#define CROP_H

#include <stdio.h>

#include "image.h"

double ***alloc_selected_matrix(image_t image, int *new_height, int *new_width);

void crop_command(image_t *image, int load_fail);

#endif
