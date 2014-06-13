#include <gnumake.h>
#include <limits.h>
#include <unistd.h>

char *func_pwd(const char *nm, unsigned int argc, char **argv) {
	char *buf = gmk_alloc(PATH_MAX);
	if (getcwd(buf, PATH_MAX) == NULL)
		buf[0] = '\0';
	return buf;
}

/*
MAKEFILE-TEST-BEGIN

test-pwd:
	test "$(EGM.pwd )" = "$(shell pwd)"

MAKEFILE-TEST-END
*/
