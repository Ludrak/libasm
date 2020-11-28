
#ifndef TESTER_H
# define TESTER_H

# include "secure_exec.h"

int		test_strlen_unit(char *str);
int		test_strcpy_unit(char *dst, char *src);
int		test_strncpy_unit(char *dst, char *src, size_t len);
int		test_strdup_unit(char *src);

#endif
