/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:47:07 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/24 19:28:17 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <snake.h>

int		show_leaderboard(void)
{
	WINDOW	*leaderboard;

	clear();
	leaderboard = subwin(stdscr, LINES / 2, COLS / 2, LINES / 4, COLS / 4);
	box(leaderboard, ACS_VLINE, ACS_HLINE);
	mvwprintw(leaderboard, 1, COLS / 4 - 4, "Leaderboard");
	mvwprintw(leaderboard, LINES / 2 - 2, COLS / 2 - 20, "[ESC]. Back to menu");
	wrefresh(leaderboard);
	while (getch() != 27)
		continue;
	free(leaderboard);
	return (2);
}

int		choose_option(void)
{
	char	c;

	while (1)
	{
		if ((c = getch()) == '1')
			return (1);
		if (c == '2')
			return (show_leaderboard());
		if (c == 27)
		{
			nodelay(stdscr, TRUE);
			c = getch();
			nodelay(stdscr, FALSE);
			if (c == ERR)
				return (0);
		}
	}
	return (2);
}

void	add_member(t_list **snake)
{
	t_list	*tmp;

	tmp = ft_lstlast(*snake);
	if (tmp->head == NORTH)
		tmp->next = ft_lstnew(tmp->pos_x + 1, tmp->pos_y, NORTH);
	if (tmp->head == SOUTH)
		tmp->next = ft_lstnew(tmp->pos_x - 1, tmp->pos_y, SOUTH);
	if (tmp->head == WEST)
		tmp->next = ft_lstnew(tmp->pos_x, tmp->pos_y + 1, WEST);
	if (tmp->head == EAST)
		tmp->next = ft_lstnew(tmp->pos_x, tmp->pos_y - 1, EAST);
}
