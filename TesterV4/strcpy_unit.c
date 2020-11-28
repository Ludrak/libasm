
#include "secure_exec.h"
#include <stdio.h>
#include <string.h>


int		test_strcpy_unit(char *dst, char *src)
{
	int		signal[2], error[2];
	char	**results[2];
	char	*allocated_dst;
	VAR_INIT

	if (dst && !(allocated_dst = strdup(dst)))
		return (-1);
	if (!dst)
		allocated_dst = NULL;
	results[0] = mmap(NULL, sizeof(char) * STBUFFMAX, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	results[1] = mmap(NULL, sizeof(char) * STBUFFMAX, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

	write (1, "| ", 2);
	TRY
		*results[0] = strcpy(allocated_dst, src);		
	CATCH(&signal[0], &error[0]);
	write (1, " | ", 3);
	TRY
		*results[1] = strdup("hellll");//strcpy(allocated_dst, src);
	CATCH(&signal[1], &error[1]);
	write(1, " |", 2);
	if (signal[0] == 0 && signal[1] ==  0)
	{
		if (*results[0] != *results[1])
		{
			printf (" -> \033[1;31mKO\033[0m : results does not match.\nstrlen:		%s\nft_strlen:	%s\n", *results[0], *results[1]);
			return (1);
		}
		else if (error[0] != error[1])
		{
			printf (" -> \033[1;31mKO\033[0m : errno does not match.\nstrlen:		%d\nft_strlen:	%d\n", error[0], error[1]);
			return (2);
		}
	}
	else if (signal[0] != signal[1])
	{
		printf (" -> \033[1;31mKO\033[0m : signals does not match.\nstrlen:		%d\nft_strlen:	%d\n", signal[0], signal[1]);
		return (3);
	}
	printf (" -> \033[1;32mOK\033[0m\n");
	return (0);
}

int main()
{
	test_strcpy_unit("", "worldvfndklsfnkladsnfldnaskfnadklsfnkladsnfkladsnfladsklf;ndklsanfl;adnsfadsklfnklads;");
}
