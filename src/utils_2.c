/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 19:16:09 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/24 19:27:23 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <snake.h>

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
	int ch;

	ch = getch();
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
