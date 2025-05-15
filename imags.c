/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-a <ntomas-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:27:51 by ntomas-a          #+#    #+#             */
/*   Updated: 2025/05/15 23:27:51 by ntomas-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	create_img(char *path, t_game *game)
{
	t_data	img;

	img.ptr = mlx_xpm_file_to_image(game->initmlx, path, &img.x, &img.y);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	return (img);
}

void	put_images(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
			choose_image(game, y, x);
	}
}

void	init_images(t_game *game)
{
	game->img.ptr = mlx_new_image(game->initmlx, game->map_width * 32,
		game->map_height * 32);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &(game->img.bpp),
		&(game->img.line_len), &(game->img.endian));
	game->floor = create_img("imagens/floor.xpm", game);
	game->wall = create_img("imagens/wall1.xpm", game);
	game->player = create_img("imagens/char.xpm", game);
	game->exit = create_img("imagens/door.xpm", game);
	game->collect = create_img("imagens/key.xpm", game);
	put_images(game);
}

void	choose_image(t_game *game, int y, int x)
{
	if (game->map[y][x] == '0' || game->map[y][x] == 'P'
		|| game->map[y][x] == 'C' || game->map[y][x] == 'E')
		mlx_put_image_to_window(game->initmlx, game->winmlx, game->floor.ptr, x
			* 32, y * 32);
	if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->initmlx, game->winmlx, game->player.ptr, x
			* 32, y * 32);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->initmlx, game->winmlx, game->collect.ptr,
			x * 32, y * 32);
	else if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->initmlx, game->winmlx, game->wall.ptr, x
			* 32, y * 32);
	else if (game->map[y][x] == 'E')
		mlx_put_image_to_window(game->initmlx, game->winmlx, game->exit.ptr, x
			* 32, y * 32);
}

void	refresh_graphics_player(t_game *game, int x, int y, char flag)
{
	mlx_clear_window(game->initmlx, game->winmlx);
	put_images(game);
	mlx_put_image_to_window(game->initmlx, game->winmlx, game->floor.ptr, x
		* 32, y * 32);
	mlx_put_image_to_window(game->initmlx, game->winmlx, game->exit.ptr,
		game->exit_x * 32, game->exit_y * 32);
	if (flag == 'w')
		to_complete(game, x, y - 1);
	else if (flag == 'a')
		to_complete(game, x - 1, y);
	else if (flag == 's')
		to_complete(game, x, y + 1);
	else if (flag == 'd')
		to_complete(game, x + 1, y);
}
