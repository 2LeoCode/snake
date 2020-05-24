/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:38:30 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/24 05:00:03 by lsuardi          ###   ########.fr       */
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

t_list	*ft_lstnew(int x, int y, t_head head)
{
	t_list	*tmp;

	if (!(tmp = malloc(sizeof(t_list))))
		return (NULL);
	tmp->head = head;
	tmp->pos_x = x;
	tmp->pos_y = y;
	tmp->next = NULL;
	return (tmp);
}

t_bool	ft_kbhit(void)
{
    int ch = getch();

    if (ch != ERR)
	{
        ungetch(ch);
        return (true);
    }
	else
        return (false);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*head;

	if (!lst || !*lst)
		return ;
	head = (*lst)->next;
	free(*lst);
	*lst = NULL;
	ft_lstclear(&head);
}

void	ft_wait(double seconds)
{
	clock_t		time_to_wait;

	time_to_wait = clock() + (clock_t)(seconds * CLOCKS_PER_SEC);
	while (clock() < time_to_wait)
		continue ;
}
