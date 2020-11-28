
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

#define VAR_INIT	int			pid; \
					int			sc_status, *sc_errno; \
					sc_errno = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0); \
					*sc_errno = 0;

	
#define TRY			if ((pid = fork()) < 0)  \
						fprintf (stderr, "Fork Error"); \
					if (pid == 0) \
					{ \
						errno = 0;

#define CATCH(SIGNAL, ERRNO)	*sc_errno = errno; \
								if (*sc_errno == 0) \
									fprintf (stdout, "\033[1;32m✓    VALID\033[0m"); \
								exit(0); \
							} \
							if (waitpid(pid, &sc_status, 0) != -1) \
							{ \
								*SIGNAL = WTERMSIG(sc_status); \
								*ERRNO = *sc_errno; \
								if (WIFSIGNALED(sc_status)) \
									fprintf (stderr, "\033[1;31mx SIGNALED\033[0m"); \
								else if (*sc_errno != 0) \
									fprintf (stderr, "\033[1;33mØ    ERRNO\033[0m"); \
							} 

#endif