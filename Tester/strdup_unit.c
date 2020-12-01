
#include "secure_exec.h"
#include "libasm.h"

int		test_strdup_unit(char *src)
{
	int		signal[2], error[2];
	char	**results[2];
	VAR_INIT

	results[0] = mmap(NULL, sizeof(char *), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	results[1] = mmap(NULL, sizeof(char *), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	*results[0] = mmap(NULL, sizeof(char) * STBUFFMAX, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	*results[1] = mmap(NULL, sizeof(char) * STBUFFMAX, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

	write (1, "| ", 2);
	TRY
		char *buf = strdup(src);
		strcpy(*results[0], buf);
	CATCH(&signal[0], &error[0]);
	write (1, " | ", 3);
	TRY
		char *buf = ft_strdup(src);
		strcpy(*results[1], buf);
	CATCH(&signal[1], &error[1]);
	write(1, " |", 2);
	if (signal[0] == 0 && signal[1] ==  0)
	{
		if (strcmp(*results[0], *results[1]))
		{
			printf (" -> \033[1;31mKO\033[0m : results does not match.\nstrdup:		\"%s\"\nft_strdup:	\"%s\"\n", *results[0], *results[1]);
			return (1);
		}
		else if (error[0] != error[1])
		{
			printf (" -> \033[1;31mKO\033[0m : errno does not match.\nstrdup:		%d\nft_strdup:	%d\n", error[0], error[1]);
			return (2);
		}
	}
	else if (signal[0] != signal[1])
	{
		printf (" -> \033[1;31mKO\033[0m : signals does not match.\nstrdup:		%d\nft_strdup:	%d\n", signal[0], signal[1]);
		return (3);
	}
	printf (" -> \033[1;32mOK\033[0m\n");
	return (0);
}
