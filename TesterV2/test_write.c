#include "tester.h"

static int  _TEST_WRITE(int fdw, void *buf, size_t nbuf, ssize_t (test_write)(int, const void *, size_t), ssize_t *result, char **written)
{
    int fd[2], fdws[2], i = 0;
    pipe(fd);
    pipe(fdws);

    fflush(stdout);
    pid_t   pid = fork();

    if (pid == -1)
    {
        perror("Fork error.");
        return (EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(fdws[0]);
        dup2(fdws[1], fdw);
        if (result)
            *result = test_write(fdw, buf, nbuf);
        printf ("\033[1;32m✓ %5ld\033[0m", *result);
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

    close(fd[1]);
    dup(fd[0]);
    read(fd[0], result, sizeof(ssize_t));

    if (buf)
    {
        if (!(*written = malloc(ft_strlen(buf) + 1)))
            return (-1);
        bzero(*written, strlen(buf) + 1);
        close(0);
        close(fdws[1]);
        dup(fdws[0]);
        read(fdws[0], *written, strlen(buf));
    }
    else
        *written = NULL;


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

#define     TESTFILE_NAME "test_file.txt"
static int   __clears_fd(int *fd)
{
    if (fcntl(*fd, F_GETFD))
        close(*fd);
    remove(TESTFILE_NAME);
    if (!(*fd = open(TESTFILE_NAME, O_RDWR | O_CREAT)))
        return (-1);
}

int         _TEST_WRITE_UNIT(int fd, void *buf, size_t nbuf, int fd_invalid)
{
    static int  unit_test = 1;
    ssize_t r1 = -1, r2 = -1;
    char    *b1, *b2;

    printf ("%2d | ", unit_test++);


    if (!fd_invalid)
        __clears_fd(&fd);
    _TEST_WRITE(fd, buf, nbuf, write, &r1, &b1);
    if (!fd_invalid)
        remove("test_file.txt");

    printf(" | ");

    if (!fd_invalid)
        __clears_fd(&fd);
    _TEST_WRITE(fd, buf, nbuf, write, &r2, &b2);
    if (!fd_invalid)
        remove("test_file.txt");

    if (r2 == r1 && ((b1 == NULL && b2 == NULL) || strcmp(b1, b2) == 0))
        printf (" | -> \033[1;32mOK\033[0m");
    else {
        printf (" | -> \033[1;31mKO\033[0m :");
        if (r2 && r1 && r2 != r1)
            printf (" returned %ld instead of %ld", r2, r1);
        if ((b1 != b2) || (b1 && b2 && strcmp(b1, b2) != 0))
            printf (" written \"%s\" instead of \"%s\"", b2, b1);
    }
    free(b1);
    free(b2);
    printf ("\n");
}
