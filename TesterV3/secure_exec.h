
#ifndef SECURE_EXEC_H
# define SECURE_EXEC_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/ptrace.h>


# define VAR_INIT		int			pid, pipe_fd[2], err, status; \
						char		errno_buf[2];

# define EXEC_APART		pipe(pipe_fd); \
						if ((pid = fork()) < 0) \
							fprintf (stderr, "Fork Error"); \
						if (pid == 0) \
						{


# define PRINT_LOGBACK		fprintf (stdout, "\033[1;32m✓ \033[0m"); \
							errno = 0; \
							err = errno; \
							errno_buf[0] = (err / 10 == 0) ? ' ' : (err / 10 + '0'); \
							errno_buf[1] = (err % 10) + '0'; \
							write(pipe_fd[1], errno_buf, 2); \
							close(pipe_fd[1]); \
							exit(0); \
						} \
						close(pipe_fd[1]); \
						if (waitpid(pid, &status, 0) != -1) \
						{ \
							char	buf[3]; \
							buf[2] = 0; \
							if (WIFSIGNALED(status)) \
								fprintf (stderr, "\033[1;31mx\033[0m Signal: %d", status); \
							else \
							{ \
								read(pipe_fd[0], buf, 2); \
								printf ("Errno: %s", buf); \
							} \
						} \
						close(pipe_fd[0]); \
						printf ("\n");

#endif
