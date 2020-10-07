
#ifndef LIBASM_H
# define LIBASM_H

# include <errno.h>
# include <stdlib.h>

typedef unsigned long int t_size;

typedef struct  s_list
{
    void            *data;
    struct s_list   *next;
}               t_list;

/*
**  LIBASM - I/O
*/
t_size		ft_write(int fd, void *buf, t_size len);
t_size		ft_read(int fd, void *buf, t_size len);

/*
**  LIBASM - STRINGS
*/
t_size		ft_strlen(const char *str);
int			ft_strcmp(char *str1, char *str2);
char		*ft_strcpy(char *dst, char *src);
char		*ft_strncpy(char *dst, char *src, t_size len);
char        *ft_strdup(char *str);

/*
**  LIBASM - LISTS
*/
t_list      *ft_list_push_front(t_list **alst, t_list *lst);
t_size      ft_list_size(t_list *lst);

#endif