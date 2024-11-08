
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
		t = malloc(BUFFER_SIZE * sizeof(char));
	nbuf = 0;
	check = 0;
	c = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!c)
		return (NULL);
	add_to_c(c, t, &nbuf);
	if (ft_isnewline(t))
		return t;
	while (!check)
	{
		sr = read(fd, c + nbuf, BUFFER_SIZE);
		if (!sr)
			return (NULL);
		check = ft_isnewline(c + nbuf);
		temp = ft_strdup(c);
		if (!temp)
			return (NULL);
		free(c);
		c = (char *)malloc(sizeof(char) * (nbuf + 1 + BUFFER_SIZE));
		if (!c)
			return (c);
		c = ft_strcpy(c, temp);
		nbuf += sr;
		free(temp);
	}
	c[nbuf] = '\0';
	add_to_tiroir(c, t);
	c[is_end_of_line(c)] = '\0';
	return (c);
}

int	main(void)
{
	int fd;
	char *str;

	fd = open("test", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s\n", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);

	return (0);
}