// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "basic.h"

// Selects the whole image
void select_all(image_t *image)
{
	image->c[0][0] = 0;
	image->c[0][1] = image->width;
	image->c[1][0] = 0;
	image->c[1][1] = image->height;
}

// Checks the parameter for SELECT
int check_arg_select(char *check)
{
	if (strstr(check, "ALL"))
		return 1;

	for (unsigned long i = 0; i < strlen(check); ++i)
		if (check[i] >= '0' && check[i] <= '9')
			return 1;

	return 0;
}

// Continues the SELECT command is all is well
void continue_select(image_t *image, int new_x1, char *tok)
{
	// Stores if the coordinates are invalid
	int err_c = 0;
	// Stores the number of coordinates
	int n_coord = 0;
	int new_x2, new_y1, new_y2;

	// Gets the next coordinate
	tok = strtok(NULL, " ");
	while (tok) {
		// Stops if it is invalid
		if (!check_arg_select(tok))
			break;

		// Adds 1 to the number of coordinates
		++n_coord;

		// Turns the coordinates to ints
		if (n_coord == 1)
			new_y1 = atoi(tok);
		else if (n_coord == 2)
			new_x2 = atoi(tok);
		else if (n_coord == 3)
			new_y2  = atoi(tok);

		// Stops If the number of coordinates is over 3
		if (n_coord > 3)
			break;

		// Gets the next coordinate
		tok = strtok(NULL, "\n ");
	}
		if (n_coord >= 3) {
			int h = image->height;
			int w = image->width;
			// Checks if the coordinates are invalid
			if (new_x2 > w || new_y1 > h || new_y2 > h) {
				printf("Invalid set of coordinates\n");
				err_c = 1;
			} else if (new_x2 < 0 || new_y1 < 0 || new_y2 < 0) {
				printf("Invalid set of coordinates\n");
				err_c = 1;
			} else if (new_x1 - new_x2 == 0 || new_y1 - new_y2 == 0) {
				printf("Invalid set of coordinates\n");
				err_c = 1;
			} else {
				// Stores the new coordinates
				image->c[0][0] = new_x1;
				image->c[0][1] = new_x2;
				image->c[1][0] = new_y1;
				image->c[1][1] = new_y2;

				// Swaps them if they are reversed
				if (image->c[0][0] > image->c[0][1])
					swap_values(&image->c[0][0], &image->c[0][1]);
				if (image->c[1][0] > image->c[1][1])
					swap_values(&image->c[1][0], &image->c[1][1]);
			}
		} else {
			printf("Invalid command\n");
		}

		// Prints the appropiate messages if the coordinates
		// are not invalid
		if (n_coord >= 3 && err_c == 0) {
			printf("Selected %d %d ", image->c[0][0], image->c[1][0]);
			printf("%d %d\n", image->c[0][1], image->c[1][1]);
		}
}

// Does the SELECT command
void select_command(image_t *image, int load_fail, char *tok)
{
	int new_x1;

	// Returns if LOAD failed
	if (load_fail == 1) {
		fprintf(stdout, "No image loaded\n");
	} else {
		// Gets the parameter, "ALL" or the first coordinate
		tok = strtok(NULL, "\n ");

		// Returns if SELECT does not have a parameter after it
		if (!tok) {
			printf("Invalid command\n");
			return;
		}

		if (check_arg_select(tok) == 0) {
			printf("Invalid command\n");
		} else {
			// Checks if the parameter is ALL,
			// then selects the whole image
			if (strstr(tok, "ALL")) {
				select_all(image);
				printf("Selected ALL\n");
			} else {
				// Turns the first coordinate to int
				new_x1 = atoi(tok);

				// Continues the SELECT command if the
				// first parameter is not invalid
				if (new_x1 > image->width || new_x1 < 0)
					printf("Invalid set of coordinates\n");
				else
					continue_select(image, new_x1, tok);
			}
		}
	}
}
