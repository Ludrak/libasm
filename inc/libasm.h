
#ifndef LIBASM_H
# define LIBASM_H

# include <errno.h>
# include <stdlib.h>


/*
**  LIBASM - I/O
*/
size_t		ft_write(int fd, void *buf, size_t len);
size_t		ft_read(int fd, void *buf, size_t len);

/*
**  LIBASM - STRINGS
*/
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t n);
char        *ft_strdup(const char *str);

#endif

