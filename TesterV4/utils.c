
#include "secure_exec.h"



void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)s + n;
	while (n > 0)
	{
		n--;
		tmp--;
		*tmp = 0;
	}
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		*ptr;

	if (!(ptr = malloc(nmemb * size)))
		return (0);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int			ft_atoi(const char *nptr)
{
	int				sign;
	unsigned long	num;
	unsigned long	max;

	sign = 1;
	num = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	max = sign < 0 ? 9223372036854775808UL : 9223372036854775807L;
	while (ft_isdigit(*nptr))
		num = (10 * num) + (*nptr++ - '0');
	if (num > max)
		return (sign < 0 ? 0 : -1);
	return (num * sign);
}

int		ft_count(int n)
{
	int		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int				sign;
	char			*result;
	int				i;
	unsigned int	nb;

	nb = (n < 0) ? -n : n;
	sign = n < 0;
	i = ft_count(n) + sign;
	if (!(result = ft_calloc((ft_count(n) + 1 + sign), sizeof(*result))))
		return (0);
	if (n == 0)
	{
		result[0] = '0';
		return (result);
	}
	result[0] = '-';
	while (nb)
	{
		result[--i] = nb % 10 + '0';
		nb /= 10;
	}
	return (result);
}

