#include "util.h"
#include <string.h>

void strtr_in_place(char *s, size_t l, char from, char to) {
	char *e = s + l;
	while (s < e) {
		char *p = memchr(s, from, e - s);
		if (p == NULL)
			break;
		*p = to;
		s = p + 1;
	}
}

void replace_cr_ln_in_place(char *s, size_t l) {
	strtr_in_place(s, l, '\r', ' ');
	strtr_in_place(s, l, '\n', ' ');
}
