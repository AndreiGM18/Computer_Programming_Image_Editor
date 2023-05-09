// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>

// Checks if malloc succeeds amd if not frees
// the previously allocated memory
void mem_err3(double ***p)
{
	if (!p) {
		fprintf(stderr, "Could not allocate memory\n");
		free(p);
		exit(-1);
	}
}

// Checks if malloc succeeds amd if not frees
// the previously allocated memory
void mem_err2(double ***p, int curr_line)
{
	if (!p[curr_line]) {
		fprintf(stderr, "Could not allocate memory\n");

		for (int i = 0; i < curr_line; ++i)
			free(p[i]);
		free(p);

		exit(-1);
	}
}

// Checks if malloc succeeds amd if not frees
// the previously allocated memory
void mem_err1(double ***p, int curr_line, int curr_col)
{
	if (!p[curr_line][curr_col]) {
		fprintf(stderr, "Could not allocate memory\n");

		for (int i = 0; i < curr_line; ++i) {
			for (int j = 0; j < curr_col; ++j)
				free(p[i][j]);
			free(p[i]);
		}
		free(p);

		exit(-1);
	}
}
