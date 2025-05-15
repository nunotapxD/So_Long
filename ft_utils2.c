/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-a <ntomas-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:27:43 by ntomas-a          #+#    #+#             */
/*   Updated: 2025/05/15 23:27:43 by ntomas-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flod_fill(char **map, int x, int y, int *count)
{
	if (map[y][x] == 'C' || map[y][x] == 'E')
		*count += 1;
	map[y][x] = 'F';
	if (map[y][x + 1] != '1' && map[y][x + 1] != 'F')
		flod_fill(map, x + 1, y, count);
	if (map[y][x - 1] != '1' && map[y][x - 1] != 'F')
		flod_fill(map, x - 1, y, count);
	if (map[y + 1][x] != '1' && map[y + 1][x] != 'F')
		flod_fill(map, x, y + 1, count);
	if (map[y - 1][x] != '1' && map[y - 1][x] != 'F')
		flod_fill(map, x, y - 1, count);
}

int	handle_ff(t_game *game)
{
	int		count;
	char	**map_tmp;
	int		i;

	map_tmp = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_tmp)
		return (0);
	count = 0;
	i = -1;
	while (game->map[++i])
		map_tmp[i] = ft_strdup(game->map[i]);
	map_tmp[i] = NULL;
	flod_fill(map_tmp, game->player_x, game->player_y, &count);
	ft_free(map_tmp);
	return (count == game->collect_count + game->exit_count);
}
