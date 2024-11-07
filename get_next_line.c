#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 10

int     ft_strlen(char *str)
{
        int     i;

        i = 0;
        while (str[i])
                i++;
        return (i);
}

int     is_end_of_line(char *c)
{
        int     i;

        i = 0;
        while (c[i])
        {
                if (c[i] == '\n')
                        return (i);
                i++;
        }
        return (i);
}
int     ft_isnewline(char *s)
{
        int     i;

        i = 0;
        while (s[i])
        {
                if (s[i] == '\n')
                        return (1);
                i++;
        }
        if (s[i] == '\0' && i < BUFFER_SIZE)
                return (1);
        return (0);
}

void    add_to_tiroir(char *c, char *t, int len)
{
        int     i;
        int     k;

        k = 0;
        i = 0;
        while (c[i] != '\n' && c[i])
                i++;
        i++;
        while (c[i] && k < 512) // buf
                t[k++] = c[i++];
}

void    re_arrange_t(char *t)
{
        int     i;
        int     k;

        i = 0;
        while (t[i] != '\n' && t[i])
                i++;
        i++;
        k = i;
        while (t[k])
        {
                t[k - i] = t[k];
                k++;
        }
        while ((k - i) < 512) // buf
        {
                t[k - i] = '\0';
                k++;
        }
}

void    add_to_c(char *c, char *t, int *nbuf)
{
        int     i;

        i = 0;
        if (t[0] == '\0')
                return ;
        else
        {
                while (i < ft_strlen(t))
                {
                        c[i] = t[i];
                        i++;
                }
                c[i] = '\n';
        }
        *nbuf = ft_strlen(t);
        re_arrange_t(t);
}

char    *get_next_line(int fd)
{
        static char     *t = NULL;
        int                     check;
        int                     nbuf;
        int                     sr;
        char            *c;

        if (t == NULL)
                t = malloc(512 * sizeof(*t));
        nbuf = 0;
        check = 0;
        c = (char *)malloc(1000 * sizeof(char));
        if (!c)
                return (NULL);
        add_to_c(c, t, &nbuf);
        while (!check)
        {
                sr = read(fd, &c[nbuf], BUFFER_SIZE);
                if (!sr)
                        break ;
                check = ft_isnewline(c);
                nbuf += sr;
        }
        c[nbuf] = '\0';
        add_to_tiroir(c, t, ft_strlen(c));
        c[is_end_of_line(c)] = '\0';
        printf("result of get_next_line() : %s\n", c);
        return (NULL);
}

int     main(void)
{
        int fd;

        fd = open("test", O_RDONLY);
        get_next_line(fd);
        get_next_line(fd);
        get_next_line(fd);
        get_next_line(fd);

        return (0);
}