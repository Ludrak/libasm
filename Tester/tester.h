#ifndef TESTER_H
# define TESTER_H

#include "libasm.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int     _TEST_STRLEN_UNIT(char *str);
int     _TEST_STRCMP_UNIT(char *str1, char *str2);
int     _TEST_STRCPY_UNIT(char *dst, char *src, size_t dst_size, size_t src_size);
int     _TEST_STRNCPY_UNIT(char *dst, char *src, size_t n, size_t dst_size, size_t src_size);
int     _TEST_STRDUP_UNIT(char *src);


#endif