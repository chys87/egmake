#pragma once

#include <stddef.h>

void strtr_in_place(char *s, size_t l, char from, char to);

// Replace '\r' and '\n' with spaces
void replace_cr_ln_in_place(char *, size_t);
