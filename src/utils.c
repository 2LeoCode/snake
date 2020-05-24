/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:38:30 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/24 19:16:01 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <snake.h>

static int		ft_isdigit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

static int		ft_isspace(char c)
{
	return (c == '\n' || c == '\t' || c == '\r'
	|| c == '\f' || c == '\v' || c == ' ');
}

int				ft_atoi(const char *str)
{
	long	nb;
	long	neg;

	nb = 0;
	neg = 1;
	while (ft_isspace(*str))
		str++;
	if (((*str == '-') || (*str == '+')) && (*(str++) == '-'))
		neg = -1;
	while (ft_isdigit(*str))
		nb = 10 * nb - 48 + (int)*(str++);
	return ((int)(neg * nb));
}

static void		ft_fputc(int fd, char c)
{
	if (fd > 0)
		write(fd, &c, 1);
}

void			ft_fputs(int fd, char *s)
{
	if (!s)
		ft_fputs(fd, "(null)");
	while (*(s++))
		ft_fputc(fd, *(s - 1));
}
