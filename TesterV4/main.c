
#include "tester.h"

int main(void)
{

	printf ("\n-> TEST ft_strlen\n\033[0;90m###########################\033[0m\n\033[4;37m| strlen     | ft_strlen  |\033[0m\n");
	test_strlen_unit("Hello World");
	test_strlen_unit("");
	test_strlen_unit(NULL);
	test_strlen_unit("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

/*	printf ("\n\n-> TEST ft_strcpy\n\033[0;90m###########################\033[0m\n\033[4;37m| strcpy     | ft_strcpy  |\033[0m\n");
	test_strcpy_unit("hello", "world");
	test_strcpy_unit("helloooo", "world");
	test_strcpy_unit("hello", "worldddd");
	test_strcpy_unit(NULL, "world");
	test_strcpy_unit("hello", NULL);
	test_strcpy_unit(NULL,  NULL);

	printf ("\n\n-> TEST ft_strncpy\n\033[0;90m###########################\033[0m\n\033[4;37m| strncpy    | ft_strncpy |\033[0m\n");
	test_strncpy_unit("Hello", "World", 3);
	test_strncpy_unit("Hellooo", "World", 7);
	test_strncpy_unit("Hello", "Worlddd", 7);
	test_strncpy_unit("Hello", NULL, 4);
	test_strncpy_unit("Hello", NULL, 0);
	test_strncpy_unit(NULL, "World", 3);
	test_strncpy_unit("", "World", 3);
	test_strncpy_unit("Hello", "", 3);
	test_strncpy_unit("Hello", "World", 7);
	test_strncpy_unit("Hello", "World", -1);

	printf ("\n\n-> TEST ft_strdup\n\033[0;90m###########################\033[0m\n\033[4;37m| strdup     | ft_strdup  |\033[0m\n");
	test_strdup_unit("Hello");
	test_strdup_unit("HelloWOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOORLD");
	test_strdup_unit("");
	test_strdup_unit(NULL);*/
	return (0);
}
