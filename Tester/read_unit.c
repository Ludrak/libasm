
#include "secure_exec.h"
#include "libasm.h"

int		test_read_unit(int fd, char *buf, size_t size)
{
	int		signal[2], error[2];
	ssize_t	*results[2];
	char	*read_results[2];
	int		fd_pipe[2];
	VAR_INIT
	
	if (fd > 0)
		pipe(fd_pipe);
	else
		fd_pipe[0] = fd;

	if (!(results[0] = mmap(NULL, sizeof(size_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0)) ||
	 !(results[1] = mmap(NULL, sizeof(size_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0)))
		 return (1);
	if (size < MAX_ALLOC_SZ)
	{
		if (!(read_results[0] = mmap(NULL, sizeof(char) * size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0)) ||
	 	!(read_results[1] = mmap(NULL, sizeof(char) * size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0)))
			 return (1);
	}
	fcntl(fd_pipe[0], F_SETFL, fcntl(fd_pipe[0], F_GETFL) | O_NONBLOCK);
	fcntl(fd_pipe[1], F_SETFL, fcntl(fd_pipe[1], F_GETFL) | O_NONBLOCK);
	write (1, "| ", 2);
	if (fd > 0)
		write(fd_pipe[1], buf, size);
	TRY
		close(fd_pipe[1]);
		*results[0] = read(fd_pipe[0], read_results[0], size);
	CATCH(&signal[0], &error[0]);

	write (1, " | ", 3);
	if (fd > 0)
		write (fd_pipe[1], buf, size);
	TRY
		close(fd_pipe[1]);
		*results[1] = ft_read(fd_pipe[0], read_results[1], size);
	CATCH(&signal[1], &error[1]);

	write(1, " |", 2);
	close(fd_pipe[0]);
	close(fd_pipe[1]);	
	if (signal[0] == 0 && signal[1] ==  0)
	{
		if (error[0] != error[1])
		{
			printf (" -> \033[1;31mKO\033[0m : errno does not match.\nread:		%d\nft_read:	%d\n", error[0], error[1]);
			return (2);
		}
		else if (*results[0] != *results[1])
		{
			printf (" -> \033[1;31mKO\033[0m : results does not match.\nread:		%zu\nft_read:	%zu\n", *results[0], *results[1]);
			return (1);
		}
		else if (fd > 0 && size < MAX_ALLOC_SZ && strcmp(read_results[0], read_results[1]))
		{
			printf (" -> \033[1;31mKO\033[0m : read results does not match.\nread:		%zu\nft_read:	%zu\n", *results[0], *results[1]);
			return (1);
		}
	}
	else if (signal[0] != signal[1])
	{
		printf (" -> \033[1;31mKO\033[0m : signals does not match.\nread:		%d\nft_read:	%d\n", signal[0], signal[1]);
		return (3);
	}
	printf (" -> \033[1;32mOK\033[0m\n");
	return (0);
}
