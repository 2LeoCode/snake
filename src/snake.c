/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:37:17 by lsuardi           #+#    #+#             */
/*   Updated: 2020/05/24 20:55:27 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <snake.h>

static int		main_menu(void)
{
	WINDOW	*menu;
	int		ret;

	clear();
	menu = subwin(stdscr, LINES / 2, COLS / 2, LINES / 4, COLS / 4);
	box(menu, ACS_VLINE, ACS_HLINE);
	mvwprintw(menu, 1, COLS / 4 - 4, "Main menu");
	mvwprintw(menu, 3, 1, "1. Start Game");
	mvwprintw(menu, 4, 1, "2. Leaderboard");
	mvwprintw(menu, LINES / 2 - 2, COLS / 2 - 18, "[ESC]. Leave Game");
	wrefresh(menu);
	free(menu);
	if ((ret = choose_option()) == 2)
		return (main_menu());
	return (ret);
}

static void		game_over(unsigned int score)
{
	WINDOW	*death_screen;

	nodelay(stdscr, FALSE);
	beep();
	clear();
	if (!(death_screen = subwin(stdscr, LINES / 2, COLS / 2,
	LINES / 4, COLS / 4)))
		exit(EXIT_FAILURE);
	box(death_screen, ACS_VLINE, ACS_HLINE);
	mvwprintw(death_screen, (LINES / 4) - 1, (COLS / 4) - 4, "GAME OVER");
	mvwprintw(death_screen, (LINES / 4), (COLS / 4) - 4, "Score: %u", score);
	mvwprintw(death_screen, (LINES / 4) + 1, (COLS / 4) - 18,
	"Press any key to go back to main menu.");
	refresh();
	getch();
	nodelay(stdscr, TRUE);
}

static void		start_game(WINDOW *game, t_list **snake,
unsigned int score, double speed)
{
	int				tmp;
	t_head			face;
	t_coords		bonus;

	face = NORTH;
	bonus = generate_bonus();
	while (1)
	{
		if (ft_kbhit())
		{
			if (((tmp = get_direction(face)) < 0) && pause_menu())
				break ;
			else
				face = (((tmp == (int)face - 2) || (tmp == (int)face + 2)) ?
				face : (unsigned int)tmp);
		}
		if ((tmp = get_elems(snake, &bonus, face, &speed)) == -1)
		{
			game_over(score);
			return ;
		}
		score += tmp;
		display_elems(*snake, bonus, game);
		ft_wait(speed);
	}
}

static int		snake(void)
{
	WINDOW			*game;
	t_list			*snake;
	unsigned int	score;
	double			speed;

	score = 0;
	speed = 0.3;
	snake = ft_lstnew(WIN_X / 2, WIN_Y / 2, NORTH);
	if (!(game = subwin(stdscr, WIN_X, WIN_Y,
	(LINES / 2) - (WIN_X / 2), (COLS / 2) - (WIN_Y / 2))))
		return (-1);
	init_game(snake, game);
	nodelay(stdscr, TRUE);
	start_game(game, &snake, score, speed);
	free(game);
	ft_lstclear(&snake);
	return (0);
}

int				main(void)
{
	initscr();
	noecho();
	while (1)
		if (!main_menu() || snake())
			break ;
	endwin();
	return (0);
}
