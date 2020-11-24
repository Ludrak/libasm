#include "tester.h"

static int  _TEST_READ(int fdr, size_t nbuf, ssize_t (test_read)(int, void *, size_t), ssize_t *result, char **read_val, char *to_read)
{
    int fd[2], fdrs[2], i = 0;
    pipe(fd);
    pipe(fdrs);

    fflush(stdout);
    pid_t   pid = fork();

    if (pid == -1)
    {
        perror("Fork error.");
        return (EXIT_FAILURE);
    }

    if (pid == 0)
    {

        // (fdrs[1], to_read, strlen(to_read));
        if (result)
            *result = test_read(fdr, *read_val, nbuf);

       // printf ("r: %s\n", *read_val);
        printf ("\033[1;32m✓ %5ld\033[0m", *result);
        fflush(stdout);
        close(fdrs[0]);
        if (*read_val)
            write (fdrs[1], *read_val, strlen(*read_val));

        close(fd[0]);
        close(1);
        dup(fd[1]);
        write(fd[1], result, sizeof(ssize_t));
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
    close(fd[0]);

    if (to_read)
    {
        if (!(*read_val = malloc(ft_strlen(to_read) + 1)))
            return (-1);
        bzero(*read_val, strlen(to_read) + 1);
        close(fdrs[1]);
        read(fdrs[0], *read_val, strlen(to_read));
        close(fdrs[0]);
    }
    else
        *read_val = NULL;


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
static int   __clears_fd(int *fd, char *to_read)
{
    remove(TESTFILE_NAME);
    if (fcntl(*fd, F_GETFD))
        close(*fd);
    if (!(*fd = open(TESTFILE_NAME, O_WRONLY | O_CREAT)))
        return (-1);
    if (to_read)
        write (*fd, to_read, strlen(to_read));

    close(*fd);
    if (!(*fd = open(TESTFILE_NAME, O_RDWR)))
        return (-1);

}

int         _TEST_READ_UNIT(int fd, ssize_t nbuf, char *to_read, int fd_invalid)
{
    static int  unit_test = 1;
    ssize_t r1 = -1, r2 = -1;
    char    *b1, *b2;

    printf ("%2d | ", unit_test++);

    if (!fd_invalid)
        __clears_fd(&fd, to_read);
   // read(fd, b1, nbuf);
    _TEST_READ(fd, nbuf, read, &r1, &b1, to_read);
    if (!fd_invalid)
    {
        close(fd);
        remove(TESTFILE_NAME);
    }

    printf(" | ");

    if (!(fd = open(TESTFILE_NAME, O_RDWR)))
        return (-1);
    if (!fd_invalid)
        __clears_fd(&fd, to_read);
   // read(fd, b2, nbuf);
    _TEST_READ(fd, nbuf, read, &r2, &b2, to_read);
    if (!fd_invalid)
    {
        close(fd);
        remove(TESTFILE_NAME);
    }

    if (r2 == r1 && ((b1 == NULL && b2 == NULL) || strcmp(b1, b2) == 0))
        printf (" | -> \033[1;32mOK\033[0m");
    else {
        printf (" | -> \033[1;31mKO\033[0m :");
        if (r2 && r1 && r2 != r1)
            printf (" returned %ld instead of %ld", r2, r1);
        //if ((b1 =! b2) || (b1 && b2 && strcmp(b1, b2) != 0))
    }
    if (b1 && b2)
     printf (" read \"%s\" instead of \"%s\"", b2, b1);
    free(b1);
    free(b2);
    printf ("\n");
}


/*#include "tester.h"


static int  _TEST_READ(int fdr, ssize_t nbuf, size_t (test_read)(int fd, void *buf, ssize_t nbuf), ssize_t *result, char **read_val)
{
    int fd[2], fd_read[2], i = 0;
    pipe(fd);
    pipe(fd_read);

    fflush(stdout);
    pid_t   pid = fork();

    if (pid == -1)
    {
        perror("Fork error.");
        return (EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(fd_read[0]);
        dup(fd_read[1]);
        if (result)
            *result = test_read(fdr, *read_val, nbuf);
        if (*read_val)
            write(fd_read[1], *read_val, strlen(*read_val));
        printf ("\033[1;32m✓ %5d\033[0m", *result);
        fflush(stdout);
        close(fd[0]);
        close(1);
        dup(fd[1]);
        write(1, result, sizeof(ssize_t)); 
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

    char    *BUFFER[MAX_READ_BUFFER];
    int     buf_len;

    bzero(BUFFER, MAX_READ_BUFFER);
    close(0);
    close(fd_read[1]);
    dup(fd_read[0]);
    if ((buf_len = read(fd_read[0], BUFFER, MAX_READ_BUFFER)) > 0)
    {
        if (BUFFER && !(*read_val = strdup(BUFFER)))
            return (-1);
    }

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
static int  __clears_fd(int *fd, char *to_read)
{
    if (fcntl(*fd, F_GETFD))
        close(*fd);
    remove(TESTFILE_NAME);
    if (!(*fd = open(TESTFILE_NAME, O_WRONLY | O_CREAT)))
        return (-1);
    if (to_read)
        write (fd, to_read, strlen(to_read));
    close(*fd);
    if (!(*fd = open(TESTFILE_NAME, O_RDWR)))
        return (-1);
}

int         _TEST_READ_UNIT(int fd, ssize_t nbuf, char *to_read, int fd_invalid)
{
    static int  unit_test = 1;
    int     r1 = -1, r2 = -1;
    char    *b1, *b2;

    printf ("%2d | ", unit_test++);


    if (!fd_invalid)
        __clears_fd(&fd, to_read);
    _TEST_READ(fd, nbuf, read, &r1, &b1);
    printf(" | ");
    remove(TESTFILE_NAME);

    if (!fd_invalid)
        __clears_fd(&fd, to_read);
    _TEST_READ(fd, nbuf, ft_read, &r2, &b2);
    remove(TESTFILE_NAME);

    if (r2 == r1 && ((b1 == NULL && b2 == NULL) || strcmp(b1, b2) == 0))
        printf (" | -> \033[1;32mOK\033[0m");
    else {
        printf (" | -> \033[1;31mKO\033[0m :");
        if (r2 && r1 && r2 != r1)
            printf (" returned %ld instead of %ld", r2, r1);
        if ((b1 =! b2) || (b1 && b2 && strcmp(b1, b2) != 0))
            printf (" read \"%s\" instead of \"%s\"", b2, b1);
    }
    free(b1);
    free(b2);
    printf ("\n");
}
*/
