#include "tester.h"


static int  _TEST_STRCPY(char *str1, char *str2, char *(test_strcpy)(char *, const char *), char **result)
{
    int fd[2], i = 0;
    pipe(fd);

    fflush(stdout);
    pid_t   pid = fork();

    if (pid == -1)
    {
        perror("Fork error.");
        return (EXIT_FAILURE);
    }

    if (pid == 0)
    {
        if (result)
            *result = test_strcpy(str1, str2);
        printf ("\033[1;32m✓      \033[0m");
        fflush(stdout);
        close(fd[0]);
        close(1);
        dup(fd[1]);
        write(1, *result, sizeof(*result)); 
        exit(EXIT_SUCCESS);
    }
    
    int status = -1, signal = -1;
    if (waitpid(pid, &status, 0) == -1)
    {
        perror("Fork error.");
        return (EXIT_FAILURE);
    }
    close(0);
    close(fd[1]);
    dup(fd[0]);
    read(fd[0], result, sizeof(char *));

    if (WIFEXITED(status))
    {
        signal = WEXITSTATUS(status);
        printf (" (sig: %2d)", signal);
        return (EXIT_SUCCESS);
    }

    if (WIFSIGNALED(status))
    {
        signal = WTERMSIG(status);
        printf ("\033[1;31mx CRASH\033[0m (sig: %2d)", signal);
        return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}

int         _TEST_STRCPY_UNIT(char *dst, char *src, size_t dst_size, size_t src_size)
{
    static int  unit_test = 1;
    char *dst_, *src_;
    char *r1 = NULL, *r2 = NULL;


    if (dst_size > 0 && !(dst_ = malloc(dst_size + 1)))
        return (-1);
    if (dst && dst_size > 0)
        memcpy(dst_, dst, dst_size);
    if (src_size > 0 && !(src_ = malloc(src_size + 1)))
        return (-1);
    if (src && src_size > 0)
        memcpy(src_, src, src_size);

    printf ("%2d | ", unit_test++);
    _TEST_STRCPY(dst_, src_, strcpy, &r1);

	printf(" | ");
    if(dst && dst_size > 0)
		memcpy(dst_, dst, dst_size);
    if (dst && dst_size > 0)
		memcpy(src_, src, src_size);
    _TEST_STRCPY(dst_, src_, strcpy, &r2);

    if (r2 == r1)
        printf (" | -> \033[1;32mOK\033[0m");
    else
        printf (" | -> \033[1;31mKO\033[0m : returned \"%s\" instead of \"%s\"", r2, r1);
    printf ("\n");
	return (0);
}
