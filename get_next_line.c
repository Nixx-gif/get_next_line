#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define BUFFER_SIZE 12

int ft_strlen(char *str)
{
	int i;
	while (str[i])
		i++;
	//printf("\nlen calc : %d \n\n", i);
	return (i);
}

int	is_end_of_line(char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] == '\n')
			return (i);
		else
			i++;
	}
	return (0);
}


void add_to_tiroir(char *c, char* t, int len)
{
	int i;
	int k;

	k = 0;
	i = (len - BUFFER_SIZE);
	while (c[i] != '\n' && c[i])
		i++;
	i++;
	while (c[i])
		t[k++] = c[i++];
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
		{
			c[i] = t[i];
			i++;
		}
	}
	printf(" :: %d\n", ft_strlen(t));
	t += ft_strlen(t);
	*nbuf = ft_strlen(t);
}

char *get_next_line(int fd)
{
	static char* t = NULL;
    if(t == NULL)
	    t = malloc(BUFFER_SIZE*sizeof(*t));
	int check;
	int nbuf;
	int sr;
	nbuf = 0;
	check = 0;
    char* c = (char*)calloc(1000, sizeof(char));
	if (!c)
		return (NULL);
	printf("t : %d", ft_strlen(t));
	add_to_c(c, t, &nbuf);
	printf("\ntest-second-iteration : %s || %d\n", c, nbuf);
	while (!check)
	{
		//write(1, "loop1", 5);
		sr = read(fd, &c[nbuf], BUFFER_SIZE);
		printf("c : %s\n", c);
		check = is_end_of_line(c);
		nbuf += sr;
	}
    c[nbuf] = '\0';
	add_to_tiroir(c, t, ft_strlen(c));
	c[is_end_of_line(c)] = '\0';
    printf("Those bytes are as follows: %s\n", c);
    printf("tiroirrrrr: %s\n", t);

	return 	(NULL);

}

int	main(void)
{
	int fd;

	fd = open("test", O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
	return 0;
}