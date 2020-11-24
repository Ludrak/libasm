
#ifndef LIBASM_H
# define LIBASM_H

# include <errno.h>
# include <stdlib.h>

typedef unsigned long int t_size;

/*
**  LIBASM - I/O
*/
t_size		ft_write(int fd, void *buf, t_size len);
t_size		ft_read(int fd, void *buf, t_size len);

/*
**  LIBASM - STRINGS
*/
t_size		ft_strlen(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, t_size n);
char        *ft_strdup(const char *str);

#endif

