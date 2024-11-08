/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:51:52 by nino              #+#    #+#             */
/*   Updated: 2024/11/08 15:17:04 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_end_of_line(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

int	ft_isnewline(char *s)
{
	int	i;

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

void	add_to_tiroir(char *c, char *t)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (c[i] != '\n' && c[i])
		i++;
	i++;
	while (c[i] && k < BUFFER_SIZE) // buf
		t[k++] = c[i++];
}

void	re_arrange_t(char *t)
{
	int	i;
	int	k;

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
	while ((k - i) < BUFFER_SIZE) // buf
	{
		t[k - i] = '\0';
		k++;
	}
}

void	add_to_c(char *c, char *t, int *nbuf)
{
	size_t i;

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