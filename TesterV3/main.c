
#include "secure_exec.h"

void	test_strlen_unit(char *str)
{
	static int	unit = 1;
	int	exception = 0, ft_exception = 0;
	VAR_INIT

	printf("%d | ", unit++);
	fflush(stdout);
	TRY
	{
		strlen(str);
	}
	CATCH (&exception)
	printf(" | ");
	fflush(stdout);
	TRY
	{
		strlen(str);
	}
	CATCH (&exception)
	printf(" |\n");
	fflush(stdout);
}


int main(void)
{
	test_strlen_unit("Hello world");
	test_strlen_unit("dasdasdasdasdasdasdasdasdasdasdas");
	test_strlen_unit(NULL);
}

/*
int main(void)
{
	int	exception = 0;
	int	*result = malloc(sizeof(int));
	VAR_INIT

	printf ("%p\n", result);
	*result = 0;
	TRY
	{
		*result = 3 + 5;
		printf ("%p\n", result);

		int *a = 0;
		*a = 0;
	}
	CATCH(&exception);
	if (exception != 0)
	{
		printf ("%p\n", result);
		printf ("Returned exception : %d resulted in: %d\n", exception, *result);
	}
	return (0);
}*/
