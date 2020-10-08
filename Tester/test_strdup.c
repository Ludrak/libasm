#include "tester.h"


static int  _TEST_STRDUP(char *str, char *(test_strdup)(const char *), char **result)
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
        {
            *result = test_strdup(str);
            free(*result);
            *result = test_strdup(str);
        }
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
    read(fd[0], *result, sizeof(char *));

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

int         _TEST_STRDUP_UNIT(char *src)
{
    static int  unit_test = 1;
    char *r1 = NULL, *r2 = NULL;


    printf ("%2d | ", unit_test++);
    _TEST_STRDUP(src, strdup, &r1);
    printf(" | ");
    _TEST_STRDUP(src, ft_strdup, &r2);

    if (r2 == r1)
        printf (" | -> \033[1;32mOK\033[0m");
    else
        printf (" | -> \033[1;31mKO\033[0m : returned \"%s\" instead of \"%s\"", r2, r1);
    free(r1);
    free(r2);
    printf ("\n");
}
