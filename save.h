// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>

#include "image.h"

void save_command(image_t *image, int load_fail, char *tok, int new_file_type);

void write(image_t *image, int new_file_type, FILE *f);

void write_type(image_t *image, int new_file_type, FILE *f);

#endif
