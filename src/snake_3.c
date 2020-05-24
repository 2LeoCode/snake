/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:43:39 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/24 16:49:36 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <snake.h>

t_bool	check_input(int input)
{
	return ((input >= 5) && (input <= LINES));
}

void	init_game(t_list *snake, WINDOW *game)
{
	int		count;

	count = 3;

	while (count--)
	{
		clear();
		box(game, ACS_VLINE, ACS_HLINE);
		mvwprintw(game, 3, 5, "Get ready...");
		mvwaddch(game, snake->pos_x, snake->pos_y, CHARACTER);
		mvwaddch(game, 3, 20, count + 49);
		refresh();
		sleep(1);
	}
	clear();
}

void	get_next_head(t_list **snake)
{
	t_list	*tmp;
	t_list	*head;
	
	tmp = *snake;
	head = tmp->next;
	while (head)
	{
		if (tmp->pos_x == (head->pos_x + 1))
			head->head = SOUTH;
		if (tmp->pos_x == (head->pos_x - 1))
			head->head = NORTH;
		if (tmp->pos_y == (head->pos_y + 1))
			head->head = EAST;
		if (tmp->pos_y == (head->pos_y - 1))
			head->head = WEST;
		tmp = head;
		head = head->next;
	}
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

int		check_pos(t_list *snake_head)
{
	t_list	*tmp;

	tmp = snake_head->next;
	while (tmp)
	{
		if ((snake_head->pos_x == tmp->pos_x)
		&& (snake_head->pos_y == tmp->pos_y))
			return (-1);
		tmp = tmp->next;
	}
	return (-1 * !((snake_head->pos_x > 0)
	&& (snake_head->pos_x < WIN_X - 1)
	&& (snake_head->pos_y > 0)
	&& (snake_head->pos_y < WIN_Y - 1)));
}

int		pause_menu(void)
{
	WINDOW	*pause;
	char	c;

	clear();
	nodelay(stdscr, FALSE);
	if (!(pause = subwin(stdscr, LINES / 2, COLS / 2, LINES / 4, COLS / 4)))
		exit(EXIT_FAILURE);
	box(pause, ACS_VLINE, ACS_HLINE);
	mvwprintw(pause, (LINES / 4) - 1, (COLS / 4) - 2, "PAUSE");
	mvwprintw(pause, LINES / 4, (COLS / 4) - 13, "Press any key to continue.");
	mvwprintw(pause, (LINES / 4) + 1, (COLS / 4) - 17, "Or press 1. to go back to main menu");
	refresh();
	free(pause);
	c = getch();
	nodelay(stdscr, TRUE);
	if (c == '1')
		return (1);
	return (0);
}
