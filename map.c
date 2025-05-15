/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-a <ntomas-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:28:00 by ntomas-a          #+#    #+#             */
/*   Updated: 2025/05/15 23:28:00 by ntomas-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_limits(t_game *game)
{
	int	i;
	int	j;

	j = game->map_height - 1;
	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] == '1' && game->map[j][i] == '1')
			i++;
		else
			return (0);
	}
	j = game->map_width - 1;
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] == '1' && game->map[i][j] == '1')
			i++;
		else
			return (0);
	}
	return (1);
}

int	save_map_line(t_game *game, char *line)
{
	char	**temp_map;
	int		i;

	if (!line)
		return (0);
	i = -1;
	game->map_height += 1;
	temp_map = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!temp_map)
		return (0);
	temp_map[game->map_height] = NULL;
	while (++i < game->map_height - 1)
		temp_map[i] = game->map[i];
	temp_map[i] = line;
	if (game->map)
		free(game->map);
	game->map = temp_map;
	return (1);
}

void	save_coords(t_game *game, int y, int x, int flag)
{
	if (flag == 0)
	{
		game->exit_x = x;
		game->exit_y = y;
		game->exit_count++;
	}
	if (flag == 1)
	{
		game->player_x = x;
		game->player_y = y;
		game->player_count++;
	}
}

int	read_chars(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				game->collect_count++;
			else if (game->map[y][x] == 'E')
				save_coords(game, y, x, 0);
			else if (game->map[y][x] == 'P')
				save_coords(game, y, x, 1);
			else if (game->map[y][x] != '1' && game->map[y][x] != '0')
				return (0);
		}
	}
	return (1);
}

int	read_map(t_game *game, char *filepath)
{
	int		fd;
	char	*line;

	fd = check_fd(filepath);
	while (1)
	{
		line = get_next_line(fd);
		if (!save_map_line(game, line))
			break ;
	}
	close(fd);
	if (game->map)
		game->map_width = ft_strlen(game->map[0]) - 1;
	return (1);
}
