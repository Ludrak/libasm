/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:33:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/11/26 13:28:51 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "secure_exec.h"
#include "libasm.h"

int	test_strlen_unit(char *str)
{
	static size_t	*shared_result[2];
	int				sig[2], error[2];
	VAR_INIT

	shared_result[0] = mmap(NULL, sizeof(**shared_result), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	shared_result[1] = mmap(NULL, sizeof(**shared_result), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	write (1, "| ", 2);
	TRY
		*shared_result[0] = strlen(str);
	CATCH(&sig[0], &error[0])
	fflush(stdout);
	write (1, " | ", 3);
	TRY
		*shared_result[1] = ft_strlen(str);
	CATCH (&sig[1], &error[1]);
	fflush(stdout);
	write(1, " |", 2);
	
	if (*shared_result[0] != *shared_result[1])
		fprintf (stderr, "\n-> TEST \033[1;31mFAILED\033[0m (results does not match)\nstrlen: res:	%zu\nft_strlen: res:	%zu\n\n", *shared_result[0], *shared_result[1]);
	else if (sig[0] != sig[1])
		fprintf (stderr, "\n-> TEST \033[1;31mFAILED\033[0m (signals does not match)\nstrlen: sig:	%d\nft_strlen: sig:	%d\n\n", sig[0], sig[1]);
	else if (error[0] != error[1])
		fprintf (stderr, "\n-> TEST \033[1;31mFAILED\033[0m (errno does not match)\nstrlen: errno:		%d\nft_strlen: errno:	%d\n\n", error[0], error[1]);	
	else
		printf (" -> \033[1;32mOK\033[0m\n");

	munmap(shared_result[0], sizeof(**shared_result));
	munmap(shared_result[1], sizeof(**shared_result));
	return (0);
}	

