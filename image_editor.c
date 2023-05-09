// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "mem_err.h"
#include "basic.h"
#include "load.h"
#include "select.h"
#include "rotate.h"
#include "crop.h"
#include "apply.h"
#include "save.h"
#include "exit.h"

#define LEN 1000

int main(void)
{
	char command[LEN];

	// Struct in which we store the image's data, height, width
	// max data value, image type, file type (from which it
	// was read), as well as the currently selected coordinates
	image_t image;
	image.colour = NULL;

	int load_fail = 1;
	// Gets the command in full
	while (fgets(command, LEN, stdin)) {
		// Considers the new file's type in which to write
		// as binary by default
		int new_file_type = 1;

		long len = strlen(command);

		// Adds '\0' to the command string
		if (command[len - 1] == '\n')
			command[len - 1] = '\0';

		// Changes the new file's type to ascii, if needed
		if (strstr(command, "SAVE") && strstr(command, "ascii"))
			new_file_type = 0;

		// Does the various commands
		if ((command[0] != '\0') && (command[0] != '\n')) {
			// Gets the first word of the command
			char *tok = strtok(command, "\n ");
			if (!tok)
				return 0;
			else if (strstr(tok, "EXIT"))
				exit_command(&image, &load_fail);
			else if (strstr(tok, "LOAD"))
				load_command(&image, &load_fail, tok);
			else if (strstr(command, "SELECT"))
				select_command(&image, load_fail, tok);
			else if (strstr(command, "ROTATE"))
				rotate_command(&image, load_fail, tok);
			else if (strstr(command, "CROP"))
				crop_command(&image, load_fail);
			else if (strstr(command, "SAVE"))
				save_command(&image, load_fail, tok, new_file_type);
			else if (strstr(command, "APPLY"))
				apply_command(&image, load_fail, tok);
			else
				fprintf(stdout, "Invalid command\n");
			}
	}
	return 0;
}
