#include <gnumake.h>

int plugin_is_GPL_compatible __attribute__((visibility("default")));

typedef char *gmk_func_type(const char *, unsigned, char **);

gmk_func_type func_cat;
gmk_func_type func_pwd;

int egmake_gmk_setup(void) __attribute__((visibility("default")));
int egmake_gmk_setup(void) {
	gmk_add_function("EGM.cat", &func_cat, 1, 0, GMK_FUNC_DEFAULT);
	gmk_add_function("EGM.pwd", &func_pwd, 0, 0, GMK_FUNC_DEFAULT);
	return 1;
}
