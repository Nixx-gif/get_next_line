
#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	while (src[len])
		len++;
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*t = NULL;
	int			check;
	int			nbuf;
	int			sr;
	char		*c;
	char		*temp;

	if (t == NULL)
		t = malloc(51200 * sizeof(*t));
	nbuf = 0;
	check = 0;
	c = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!c)
		return (NULL);
	add_to_c(c, t, &nbuf);
	while (!check)
	{
		sr = read(fd, c + nbuf, BUFFER_SIZE);
		if (!sr)
			break ;
		check = ft_isnewline(c + nbuf);
		temp = ft_strdup(c);
		if (!temp)
			return (NULL);
		free(c);
                printf("%d\n", nbuf * BUFFER_SIZE);
		c = (char *)malloc(sizeof(char) * (nbuf * BUFFER_SIZE));
		if (!c)
			return (c);
		c = ft_strcpy(c, temp);
		nbuf += sr;
		free(temp);
	}
	c[nbuf] = '\0';
	add_to_tiroir(c, t);
	c[is_end_of_line(c)] = '\0';
	printf("Tirroir: %s\n", t);
	printf("result of get_next_line() : %s\n", c);
	return (c);
}

int	main(void)
{
	int fd;

	fd = open("test", O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);

	return (0);
}