
#include "secure_exec.h"
#include "libasm.h"

int		test_write_unit(int fd, char *buf, size_t size)
{
	int		signal[2], error[2];
	size_t	*results[2];
	char	*written_results[2];
	int		fd_pipe[2];
	VAR_INIT

	
	if (fd > 0)
		pipe(fd_pipe);
	else
		fd_pipe[1] = fd;

	if (!(results[0] = mmap(NULL, sizeof(size_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0)) ||
	 !(results[1] = mmap(NULL, sizeof(size_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0)))
		 return (1);
	if (size < MAX_ALLOC_SZ)
	{
		if (!(written_results[0] = malloc(sizeof(char) * size + 1)) ||
		!(written_results[1] = malloc(sizeof(char) * size + 1)))
			return (1);
	}

	write (1, "| ", 2);

	TRY
		close(fd_pipe[0]);
		*results[0] = write(fd_pipe[1], buf, size);
	CATCH(&signal[0], &error[0]);

	write (1, " | ", 3);
	if (fd > 0 && error[0] == 0 && buf)
	{
		read(fd_pipe[0], written_results[0], size);
		written_results[0][size] = 0;
	}
	TRY
		close(fd_pipe[0]);
		*results[1] = ft_write(fd_pipe[1], buf, size);
	CATCH(&signal[1], &error[1]);

	write(1, " |", 2);
	close(fd_pipe[1]);
	if (fd > 0 && error[1] == 0 && buf)
	{
		read(fd_pipe[0], written_results[1], size);
		written_results[1][size] = 0;
	}
	close(fd_pipe[0]);	
	if (signal[0] == 0 && signal[1] ==  0)
	{
		if (error[0] != error[1])
		{
			printf (" -> \033[1;31mKO\033[0m : errno does not match.\nwrite:		%d\nft_write:	%d\n", error[0], error[1]);
			return (2);
		}
		else if (*results[0] != *results[1])
		{
			printf (" -> \033[1;31mKO\033[0m : results does not match.\nwrite:		%zu\nft_write:	%zu\n", *results[0], *results[1]);
			return (1);
		}
		else if (fd > 0 && size < MAX_ALLOC_SZ && strcmp(written_results[0], written_results[1]))
		{
			printf (" -> \033[1;31mKO\033[0m : written results does not match.\nwrite:		%zu\nft_write:	%zu\n", *results[0], *results[1]);
			return (1);
		}
	}
	else if (signal[0] != signal[1])
	{
		printf (" -> \033[1;31mKO\033[0m : signals does not match.\nwrite:		%d\nft_write:	%d\n", signal[0], signal[1]);
		return (3);
	}
	printf (" -> \033[1;32mOK\033[0m\n");
	return (0);
}
