#include "tester.h"


static int  _TEST_STRLEN(char *str, size_t (test_strlen)(const char *), int *result)
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
            *result = test_strlen(str);
        printf ("\033[1;32m✓ %5d\033[0m", *result);
        fflush(stdout);
        close(fd[0]);
        close(1);
        dup(fd[1]);
        write(1, result, sizeof(int)); 
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
    read(fd[0], result, sizeof(int));

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
        if (result)
            *result = signal;
        return (EXIT_FAILURE);
    }
}

int         _TEST_STRLEN_UNIT(char *str)
{
    static int  unit_test = 1;
    int r1 = -1, r2 = -1;

    printf ("%2d | ", unit_test++);
    _TEST_STRLEN(str, strlen, &r1);
    printf(" | ");
    _TEST_STRLEN(str, ft_strlen, &r2);

    if (r2 == r1)
        printf (" | -> \033[1;32mOK\033[0m");
    else
        printf (" | -> \033[1;31mKO\033[0m : returned %d instead of %d", r2, r1);
    printf ("\n");
}
