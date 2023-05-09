// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "basic.h"
#include "mem_err.h"

// Allocates memory for the cropped image data, then stores the values
// that remain after CROP in it
double ***alloc_selected_matrix(image_t image, int *new_height, int *new_width)
{
	// Changes the height and width
	*new_height = image.c[1][1] - image.c[1][0];
	*new_width = image.c[0][1] - image.c[0][0];

	double ***copy = (double ***)malloc(*new_height * sizeof(double **));

	mem_err3(copy);

	for (int i = 0; i < *new_height; ++i) {
		copy[i] = (double **)malloc(*new_width * sizeof(double *));
		mem_err2(copy, i);

		// Gets the number of pixels
		int n_pixels = 1;
		if (image.image_type == 2)
			n_pixels = 3;

		for (int j = 0; j < *new_width; ++j) {
			copy[i][j] = (double *)malloc(n_pixels * sizeof(double));
			mem_err1(copy, i, j);

			// Stores the selected image's data
			for (int k = 0; k < n_pixels; ++k)
				copy[i][j][k] =
					image.colour[image.c[1][0] + i][image.c[0][0] + j][k];
		}
	}

	return copy;
}

// Does the CROP command
void crop_command(image_t *image, int load_fail)
{
	// Returns if LOAD failed
	if (load_fail == 1) {
		fprintf(stdout, "No image loaded\n");
	} else {
		int new_height, new_width;

		double ***copy = alloc_selected_matrix(*image, &new_height, &new_width);

		// Frees the memory allocated for the original image data
		free_image(image);

		// Updates the coordinates
		image->c[0][0] = 0;
		image->c[0][1] = new_width;
		image->c[1][0] = 0;
		image->c[1][1] = new_height;
		image->height = new_height;
		image->width = new_width;

		// Stores the cropped image's data
		image->colour = copy;

		fprintf(stdout, "Image cropped\n");
	}
}
