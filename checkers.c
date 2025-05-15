/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-a <ntomas-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:27:30 by ntomas-a          #+#    #+#             */
/*   Updated: 2025/05/15 23:27:30 by ntomas-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	check_ac(int ac)
{
	if (ac == 2)
		return ;
	else if (ac > 2)
	{
		write(2, "Error: Too many aguments\n", 25);
		exit(EXIT_FAILURE);
	}
	else
	{
		write(2, "Error: Too few aguments\n", 24);
		exit(EXIT_FAILURE);
	}
}

int	check_fd(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error: %s: %s\n", filepath, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (!strrchr(filepath, '.') || ft_strncmp(ft_strrchr(filepath, '.'),
			".ber\0", 5) != 0)
	{
		write(2, "Error: Map not supported\n", 25);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	check_map_size(t_game *game)
{
	int	i;
	int	j;
	int	line_size;

	i = 0;
	while (game->map[++i])
	{
		j = 0;
		line_size = 0;
		while (game->map[i][j])
			if (game->map[i][j++] != '\n')
				line_size++;
		if (line_size != game->map_width)
			return (0);
	}
	return (1);
}

void	check_errors(t_game *game)
{
	if (!game->map)
		errors_map(game);
	else if (!check_map_size(game) || (game->map_height == game->map_width))
		errors_map(game);
	else if (!read_chars(game))
		errors_map(game);
	else if (!check_limits(game))
		errors_map(game);
	else if (game->collect_count < 1)
		errors_map(game);
	else if (game->exit_count != 1)
		errors_map(game);
	else if (game->player_count != 1)
		errors_map(game);
	else if (!handle_ff(game))
		errors_map(game);
}
