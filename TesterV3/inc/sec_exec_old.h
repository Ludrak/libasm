
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
# include <sys/mman.h>

char	*ft_itoa(int n);
int		ft_atoi(const char *n);


/*	VAR_INIT: defines usefull variables for try catch blocks
 */
# define VAR_INIT		int			pid, pipe_fd[2]; \
						int			sc_signal, sc_errno; \
						sc_signal = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0); \
						sc_errno = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);


/*
 *	TRY: try to run a code apart from the main process. it will handle any errors returning it's output signal
 *	Needs to be closed with CATCH or it wont compile.
 */
# define TRY			pipe(pipe_fd); \
						if ((pid = fork()) < 0) \
							fprintf (stderr, "Fork Error"); \
						if (pid == 0) \
						{ \
							errno = 0; 
/*
 *	CATCH: catches an exception and prints 
 *	SIGNAL: a (int *) that will contain the output signal of the catched exception. send NULL to ignore this return
 */
# define CATCH(SIGNAL, ERRNO) \
							err = errno; \
							if (err == 0) \
								fprintf (stdout, "\033[1;32m✓    VALID\033[0m"); \
							errno_buf = ft_itoa(err); \
							write(pipe_fd[1], errno_buf, 2); \
							close(pipe_fd[1]); \
							exit(0); \
						} \
						close(pipe_fd[1]); \
						if (waitpid(pid, &status, 0) != -1) \
						{ \
							char	buf[3]; \
							buf[2] = 0; \
							if (SIGNAL) \
								*SIGNAL = status; \
							if (WIFSIGNALED(status)) \
								fprintf (stderr, "\033[1;31mx SIGNALED\033[0m"); \
							else \
							{ \
								read(pipe_fd[0], buf, 2); \
								*ERRNO = ft_atoi(buf); \
								if (*ERRNO != 0) \
									fprintf (stderr, "\033[1;33mØ    ERRNO\033[0m");\
							} \
						} \
						close(pipe_fd[0]); 

#endif
