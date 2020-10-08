#include "tester.h"


static int  _TEST_STRNCPY(char *str1, char *str2, size_t n, char *(test_strncpy)(char *, const char *, size_t), char **result)
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
            *result = test_strncpy(str1, str2, n);
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
}

int         _TEST_STRNCPY_UNIT(char *dst, char *src, size_t n, size_t dst_size, size_t src_size)
{
    static int  unit_test = 1;
    char *dst_, *src_;
    char *r1 = NULL, *r2 = NULL;

    if (dst_size > 0 && !(dst_ = malloc(sizeof(dst_size))))
        return (-1);
    if (dst && dst_size > 0)
        memcpy(dst_, dst, dst_size);

    if (src_size > 0 && !(src_ = malloc(sizeof(src_size))))
        return (-1);
    if (src && src_size > 0)
        memcpy(src_, src, src_size);

    printf ("%2d | ", unit_test++);
    _TEST_STRNCPY(dst_, src_, n, strncpy, &r1);
    printf(" | ");
    _TEST_STRNCPY(dst_, src_, n, ft_strncpy, &r2);

    if (r2 == r1)
        printf (" | -> \033[1;32mOK\033[0m");
    else
        printf (" | -> \033[1;31mKO\033[0m : returned \"%s\" instead of \"%s\"", r2, r1);
    free(dst_);
    free(src_);
    printf ("\n");
}
