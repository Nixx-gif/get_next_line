#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define BUFFER_SIZE 5

int ft_strlen(char *str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_end_of_line(char *c)
{
	int i;
	// add end of file possibility
	i = 0;
	while (c[i])
	{
		//printf("pipi");
		if (c[i] == '\n' || c[i] == '\0')
			return (i);
		else
			i++;
	}
	if (c[i] == '\0')
		return (i);
	//printf("caca");
	return (0);
}


// void add_to_tiroir(char *c, char* t, int len)
// {
// 	int i;
// 	int k;

// 	k = 0;
// 	i = (len - BUFFER_SIZE);
// 	//printf("size i %d size len %d\n", i, len);
// 	while (c[i] != '\n' && c[i])
// 		i++;
// 	i++;
// 	while (c[i])
// 		t[k++] = c[i++];
// }

void add_to_tiroir(char *c, char* t, int len)
{
	printf("tiroir before : %s\n", t);
	printf("c use to add : %s\n", c);
	int i;
	int k;
	k = 0;
	i = 0;
	while (c[i] != '\n' && c[i])
		i++;
	i++;
	while (c[i] && k < 512) //buf
		t[k++] = c[i++];
	printf("tiroir after : %s\n", t);
}

void	re_arrange_t(char *t)
{
	int i;
	int k;
	i = 0;
	while (t[i] != '\n' && t[i])
		i++;
	i++;
	k = i;
	while (t[k])
	{
		t[k-i] = t[k];
		k++;
	}
	while ((k-i) < 512) //buf
	{
		t[k-i] = '\0';
		k++;
	}
}

void	add_to_c(char *c, char* t, int* nbuf )
{
	int i;

	i = 0;
	if (t[0] == '\0')
		return ;
	else
	{
		while (i < ft_strlen(t))
		//while (i < ft_strlen(t) && t[i] != '\n')
		{
			c[i] = t[i];
			i++;
		}
		c[i] = '\n';
	}
	//re_arrange_t(t);
	*nbuf = ft_strlen(t);
	re_arrange_t(t);
}

char *get_next_line(int fd)
{
	static char* t = NULL;
    if(t == NULL)
	    t = malloc(512*sizeof(*t));
	int check;
	int nbuf;
	int sr;
	nbuf = 0;
	check = 0;
    char* c = (char*)malloc(1000*sizeof(char));
	if (!c)
		return (NULL);
	//printf("\n add to c | c =");
	printf("Tiroir not arranged : %s\n", t);
	add_to_c(c, t, &nbuf);
	printf("Tiroir arranged : %s\n", t);
	printf("           first add to c : %s\n", c);
	while (!check)
	{
		sr = read(fd, &c[nbuf], BUFFER_SIZE);
		check = is_end_of_line(c);
		nbuf += sr;
	}
    c[nbuf] = '\0';

	add_to_tiroir(c, t, ft_strlen(c));

	c[is_end_of_line(c)] = '\0';
    printf("result of get_next_line() : %s\n", c);
    printf("tiroirrrrr: %s\n", t);

	return 	(NULL);

}

int	main(void)
{
	int fd;

	fd = open("test", O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	return 0;
}