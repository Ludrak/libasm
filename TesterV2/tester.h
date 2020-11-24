#ifndef TESTER_H
# define TESTER_H
#include "libasm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_READ_BUFFER 1024

int     _TEST_STRLEN_UNIT(char *str);
int     _TEST_STRCMP_UNIT(char *str1, char *str2);
int     _TEST_STRCPY_UNIT(char *dst, char *src, size_t dst_size, size_t src_size);
int     _TEST_STRNCPY_UNIT(char *dst, char *src, size_t n, size_t dst_size, size_t src_size);
int     _TEST_STRDUP_UNIT(char *src);
int     _TEST_WRITE_UNIT(int fd, void *buf, size_t nbuf, int fd_invalid);
int     _TEST_READ_UNIT(int fd, ssize_t nbuf, char *to_read, int fd_invalid);

#endif