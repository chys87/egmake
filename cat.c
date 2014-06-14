/*
egmake, Enhanced GNU make
Copyright (C) 2014, chys <admin@CHYS.INFO>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <gnumake.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

// Cat files, replacing '\r' and '\n' by spaces
char *func_cat(const char *nm, unsigned int argc, char **argv) {
	char *res = NULL;
	size_t L = 0;
	while (*argv) {
		const char *fname = *argv++;
		FILE *fp = fopen(fname, "r");
		if (fp == NULL) {
			free(res);
			fprintf(stderr, "Failed to open file: %s\n", fname);
			return NULL;
		}
		char buffer[4096];
		size_t l;
		while ((l = fread(buffer, 1, sizeof(buffer), fp)) != 0) {
			res = realloc(res, L + l);
			memcpy(res + L, buffer, l);
			L += l;
		}
		fclose(fp);
	}
	char *ret = gmk_alloc(L + 1);
	memcpy(ret, res, L);
	ret[L] = '\0';
	free(res);
	replace_cr_ln_in_place(ret, L);
	return ret;
}

/*
MAKEFILE-TEST-BEGIN

A := $(EGM.cat /etc/fstab)
B := $(shell cat /etc/fstab)

#ifneq '$(A)' '$(B)'
#$(error cat)
#endif

MAKEFILE-TEST-END
*/
