#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define BUFFER_SIZE 4


char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (n + 2));
	if (res == NULL)
		return (NULL);
	while (i <= n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
int	find_index(char* str)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i])
	{
		i++;
	}
	return (i);
}
void    get_next_linee(int fd)
{
	static char* string;
	int sr;
	int nbuf;
	int index;
	char *res;

	nbuf = 0;
	sr = 1;
	if(string == NULL)
	    string = malloc(BUFFER_SIZE*sizeof(char));
	while (sr != 0)
	{
		sr = read(fd, &string[nbuf], BUFFER_SIZE);
		nbuf += sr;
		string = malloc(nbuf*sizeof(char));
	}
	index = find_index(string);
	res = ft_strndup(string, index);
	printf("%s", res);
	string += index+1;

}

int	main(void)
{
	int fd;

	fd = open("test", O_RDONLY);
	get_next_linee(fd);
	get_next_linee(fd);
	get_next_linee(fd);
	get_next_linee(fd);


	return 0;
}