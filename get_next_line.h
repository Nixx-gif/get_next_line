#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
//#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

int     is_end_of_line(char *c);
int     ft_isnewline(char *s);
void    add_to_tiroir(char *c, char *t);
void    re_arrange_t(char *t);
void    add_to_c(char *c, char *t, int *nbuf);
char    *get_next_line(int fd);
size_t	ft_strlen(const char *s);


#endif