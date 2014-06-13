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
