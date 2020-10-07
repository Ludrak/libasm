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
#include <sys/ptrace.h>

int     _TEST_STRLEN_UNIT(char *str);
int     _TEST_STRLEN(char *str, t_size (f)(char *), int *result);

#endif