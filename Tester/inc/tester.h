
#ifndef TESTER_H
# define TESTER_H

# include "secure_exec.h"

int		test_strlen_unit(char *str);
int		test_strcpy_unit(char *dst, char *src);
int		test_strncpy_unit(char *dst, char *src, size_t len);
int		test_strdup_unit(char *src);
int     test_strcmp_unit(char *str1, char *str2);
int     test_write_unit(int fd, char *buf, size_t size);
int     test_read_unit(int fd, char *buf, size_t size);



#endif
