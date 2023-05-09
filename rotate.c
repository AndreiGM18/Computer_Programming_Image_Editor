// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "basic.h"
#include "mem_err.h"
#include "select.h"

// Allocates memory for a reverse copy of the image,
// then stores the necessary data in it
double ***alloc_reverse_copy(image_t image)
{
	double ***copy = (double ***)malloc(image.width * sizeof(double **));
	mem_err3(copy);

	for (int i = 0; i < image.width; i++) {
		copy[i] = (double **)malloc(image.height * sizeof(double *));
		mem_err2(copy, i);

		// Gets the number of pixels
		int n_pixels = 1;
		if (image.image_type == 2)
			n_pixels = 3;

		for (int j = 0; j < image.height; ++j) {
			copy[i][j] = (double *)malloc(n_pixels * sizeof(double));
			mem_err1(copy, i, j);

			// Gets the transpose of the matrix in
			// which the image's data is stored
			for (int k = 0; k < n_pixels; ++k)
				copy[i][j][k] = image.colour[j][i][k];
		}

		// Swaps the groups of pixels
		int l = 0, r = image.height - 1;
		while (l < r) {
			swap_pointers(&copy[i][l], &copy[i][r]);
			++l;
			--r;
		}
	}

	return copy;
}

// Rotates 90 degrees clockwise a square selected portion of the image
void rot_90_square(image_t *image)
{
	// Gets the coordinates
	int x1 = image->c[0][0];
	int x2 = image->c[0][1];
	int y1 = image->c[1][0];
	int y2 = image->c[1][1];
	// Gets the transpose of the matrix in
	// which the image's data is stored
	for (int i = y1; i < y2; ++i)
		for (int j = x1 + i - y1; j < x2; ++j) {
			int l = j - x1 + y1;
			int r = i - y1 + x1;
			swap_pointers(&image->colour[i][j], &image->colour[l][r]);
		}

	// Swaps the groups of pixels
	for (int k = image->c[1][0]; k < image->c[1][1]; ++k) {
		int l = image->c[0][0];
		int r = image->c[0][1] - 1;
		while (l < r) {
			swap_pointers(&image->colour[k][l], &image->colour[k][r]);
			++l;
			--r;
		}
	}
}

// Rotates *angle* degrees a square selected portion of the image
void rot_square(image_t *image, int angle)
{
	int pos_angle;

	// If the angle is negative, rotates the image *360 - |angle|*
	// degrees in the opposite direction, which has the same effect
	if (angle < 0 && angle > -360)
		pos_angle = 360 - (-1 * angle);
	else
		pos_angle = angle;

	// Checks if the angle is greater than 360 or less than -360
	if (pos_angle > 360 || pos_angle < -360) {
		fprintf(stdout, "Unsupported rotation angle\n");
	// Rotates 90 degrees 0 times, the angle being 0 degrees
	} else if (pos_angle % 360 == 0) {
		fprintf(stdout, "Rotated %d\n", angle);
	// Rotates 90 degrees once, the angle being 90 degrees
	} else if (pos_angle % 360 == 90) {
		rot_90_square(image);
		fprintf(stdout, "Rotated %d\n", angle);
	// Rotates 90 degrees twice, the angle being 180 degrees
	} else if (pos_angle % 360 == 180) {
		for (int i = 0; i < 2; ++i)
			rot_90_square(image);
		fprintf(stdout, "Rotated %d\n", angle);
	// Rotates 90 degrees thrice, the angle being 2700 degrees
	} else if (pos_angle % 360 == 270) {
		for (int i = 0; i < 3; ++i)
			rot_90_square(image);
		fprintf(stdout, "Rotated %d\n", angle);
	} else {
	// Checks if the angle is not a multiple of 90
		fprintf(stdout, "Unsupported rotation angle\n");
	}
}

void rot_90_full(image_t *image)
{
	// Allocates memory for a reverse copy of the image,
	// then stores the necessary data in it
	double ***copy = alloc_reverse_copy(*image);

	// Frees the old image's data
	free_image(image);

	// Swaps the height and the width of the image
	swap_values(&image->height, &image->width);

	// Selects the whole image
	select_all(image);

	// Stores the rotated image's data
	image->colour = copy;
}

void rot_full(image_t *image, int angle)
{
	int pos_angle;

	// If the angle is negative, rotates the image *360 - |angle|*
	// degrees in the opposite direction, which has the same effect
	if (angle < 0 && angle > -360)
		pos_angle = 360 - (-1 * angle);
	else
		pos_angle = angle;

	// Checks if the angle is greater than 360 or less than -360
	if (pos_angle > 360 || pos_angle < -360) {
		fprintf(stdout, "Unsupported rotation angle\n");
	// Rotates 90 degrees 0 times, the angle being 0 degrees
	} else if (pos_angle % 360 == 0) {
		fprintf(stdout, "Rotated %d\n", angle);
	// Rotates 90 degrees once, the angle being 90 degrees
	} else if (pos_angle % 360 == 90) {
		rot_90_full(image);
		fprintf(stdout, "Rotated %d\n", angle);
	// Rotates 90 degrees twice, the angle being 180 degrees
	} else if (pos_angle % 360 == 180) {
		for (int i = 0; i < 2; ++i)
			rot_90_full(image);
		fprintf(stdout, "Rotated %d\n", angle);
	// Rotates 90 degrees thrice, the angle being 270 degrees
	} else if (pos_angle % 360 == 270) {
		for (int i = 0; i < 3; ++i)
			rot_90_full(image);
		fprintf(stdout, "Rotated %d\n", angle);
	// Checks if the angle is not a multiple of 90
	} else {
		fprintf(stdout, "Unsupported rotation angle\n");
	}
}

// Does the ROTATE command
void rotate_command(image_t *image, int load_fail, char *tok)
{
	int x1 = image->c[0][0];
	int x2 = image->c[0][1];
	int y1 = image->c[1][0];
	int y2 = image->c[1][1];
	int h = image->height;
	int w = image->width;

	// Gets the angle, as a string
	tok = strtok(NULL, "\n ");

	// Returns if ROTATE does not have a parameter after it
	if (!tok) {
		printf("Invalid command\n");
		return;
	}

	// Turns the angle into an int
	int angle = atoi(tok);

	// Returns if LOAD failed
	if (load_fail == 1) {
		fprintf(stdout, "No image loaded\n");
	} else {
		// Checks if the selection is square
		if ((x2 - x1) == (y2 - y1))
			rot_square(image, angle);
		// Checks if the image is fully selected
		else if ((y1 == 0) && (x1 == 0) && (y2 == h) && (x2 == w))
			rot_full(image, angle);
		// Checks if either cases occurs
		else
			fprintf(stdout, "The selection must be square.\n");
	}
}
