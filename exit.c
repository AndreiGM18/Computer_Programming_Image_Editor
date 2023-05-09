// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "basic.h"

// Does the EXIT command, freeing all allocated memory
void exit_command(image_t *image, int *load_fail)
{
	// Exits if LOAD failed
	if (*load_fail == 1)
		fprintf(stdout, "No image loaded\n");
	// Frees all allocated memory
	else
		free_image(image);
}
