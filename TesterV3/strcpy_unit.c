/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:33:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/11/27 16:36:17 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "secure_exec.h"
#include "libasm.h"

int	test_strcpy_unit(char *dst, char *src)
{
	static char		**shared_result[2];
	int				sig[2], error[2];
	char			*allocated_args[2];
	size_t			src_len;
	VAR_INIT

	shared_result[0] = mmap(NULL, sizeof(**shared_result), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	shared_result[1] = mmap(NULL, sizeof(**shared_result), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
     
	if (src && (src_len = ft_strlen(src)))
	{
		*shared_result[0] = mmap(NULL, sizeof(char) * src_len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		*shared_result[1] = mmap(NULL, sizeof(char) * src_len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	
	}
	else
	{
		*shared_result[0] = 0;
		*shared_result[1] = 0;
	}

	allocated_args[0] = (dst) ? strdup(dst) : NULL;
	allocated_args[1] = (src) ? strdup(src) : NULL; 
	write (1, "| ", 2);
	TRY
		*shared_result[0] = strcpy(allocated_args[0], allocated_args[1]);
		free(allocated_args[0]);
		free(allocated_args[1]);
	CATCH(&sig[0], &error[0])
	fflush(stdout);
	write (1, " | ", 3);

	TRY
		*shared_result[1] = ft_strcpy(allocated_args[0], allocated_args[1]);
		free(allocated_args[0]);
		free(allocated_args[1]);
	CATCH (&sig[1], &error[1]);
	fflush(stdout);
	write(1, " |", 2);
	
	if (*shared_result && **shared_result && strcmp(*shared_result[0], *shared_result[1]) != 0)
		fprintf (stderr, "\n-> TEST \033[1;31mFAILED\033[0m (results does not match)\nstrlen: res:	\"%s\"\nft_strlen: res:	\"%s\"\n\n", *shared_result[0], *shared_result[1]);
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

