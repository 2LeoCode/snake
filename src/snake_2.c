/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:37:24 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/25 01:29:32 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <snake.h>

int			get_next_pos(t_list **snake, t_coords bonus, t_head new_head)
{
	t_list *tmp;

	tmp = *snake;
	tmp->head = new_head;
	while (tmp)
	{
		if (tmp->head == NORTH)
			tmp->pos_x--;
		if (tmp->head == EAST)
			tmp->pos_y++;
		if (tmp->head == SOUTH)
			tmp->pos_x++;
		if (tmp->head == WEST)
			tmp->pos_y--;
		tmp = tmp->next;
	}
	get_next_head(snake);
	if (((*snake)->pos_x == bonus.x) && ((*snake)->pos_y == bonus.y))
	{
		add_member(snake);
		return (1);
	}
	return (check_pos(*snake));
}

int			get_direction(t_head prev)
{
	int		map[3];
	int		i;

	i = 0;
	while (i < 3)
		map[i++] = getch();
	if ((map[0] == 27) && (map[1] == 91))
	{
		if (map[2] == UP)
			return (NORTH);
		if (map[2] == DOWN)
			return (SOUTH);
		if (map[2] == RIGHT)
			return (EAST);
		if (map[2] == LEFT)
			return (WEST);
	}
	if ((map[0] == 27) && (map[1] == ERR))
		return (-1);
	return (prev);
}

void		display_elems(t_list *snake, t_coords bonus, WINDOW *game)
{
	clear();
	box(game, ACS_VLINE, ACS_HLINE);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	wattron(game, A_BOLD);
	wattron(game, COLOR_PAIR(1));
	mvwaddch(game, bonus.x, bonus.y, '*');
	wattroff(game, COLOR_PAIR(1));
	while (snake)
	{
		mvwaddch(game, snake->pos_x, snake->pos_y, CHARACTER);
		snake = snake->next;
	}
	wattroff(game, A_BOLD);
	refresh();
}

t_coords	generate_bonus(void)
{
	t_coords tmp;

	srand(time(NULL));
	tmp.x = 1 + rand() % (WIN_X - 2);
	tmp.y = 1 + rand() % (WIN_Y - 2);
	return (tmp);
}

int			get_elems(t_list **snake, t_coords *bonus,
t_head face, double *speed)
{
	int		tmp;

	if ((tmp = get_next_pos(snake, *bonus, face)) > 0)
	{
		*bonus = generate_bonus();
		*speed /= 1.01;
		return (1);
	}
	if (tmp == -1)
		return (-1);
	return (0);
}
