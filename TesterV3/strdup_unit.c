/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:33:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/11/27 16:38:00 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "secure_exec.h"
#include "libasm.h"

int	test_strdup_unit(char *src)
{
	char			**shared_result[2];
	int				sig[2], error[2];
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

	if (shared_result[0] == MAP_FAILED || shared_result[1] == MAP_FAILED)
		return (1);
	write (1, "| ", 2);

	TRY
	{
		char *r = strdup(src);
		strcpy(*shared_result[0], r);
	}
	CATCH (&sig[0], &error[0])
	fflush(stdout);
	write (1, " | ", 3);

	TRY
	{
		char *r = strdup(src);
		strcpy(*shared_result[1], r);
	}
	CATCH (&sig[1], &error[1]);
	fflush(stdout);
	write(1, " |", 2);
	
	if (*shared_result && **shared_result &&strcmp(*shared_result[0], *shared_result[1]) != 0)
		fprintf (stderr, "\n-> TEST \033[1;31mFAILED\033[0m (results does not match)\nstrdup: res:	\"%s\"\nft_strdup: res:	\"%s\"\n\n", *shared_result[0], *shared_result[1]);
	else if (sig[0] != sig[1])
		fprintf (stderr, "\n-> TEST \033[1;31mFAILED\033[0m (signals does not match)\nstrdup: sig:	%d\nft_strdup: sig:	%d\n\n", sig[0], sig[1]);
	else if (error[0] != error[1])
		fprintf (stderr, "\n-> TEST \033[1;31mFAILED\033[0m (errno does not match)\nstrdup: errno:		%d\nft_strdup: errno:	%d\n\n", error[0], error[1]);	
	else
		printf (" -> \033[1;32mOK\033[0m\n");
	munmap(shared_result[0], sizeof(**shared_result));
	munmap(shared_result[1], sizeof(**shared_result));
	return (0);
}	

