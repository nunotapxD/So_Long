/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-a <ntomas-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:28:05 by ntomas-a          #+#    #+#             */
/*   Updated: 2025/05/15 23:28:05 by ntomas-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game game;

	check_ac(ac);
	ft_memset(&game, 0, sizeof(t_game));
	read_map(&game, av[1]);
	check_errors(&game);
	game.initmlx = mlx_init();
	game.winmlx = mlx_new_window(game.initmlx, (game.map_width * 32),
		(game.map_height * 32), "MY GAME");
	init_images(&game);
	mlx_key_hook(game.winmlx, &controls, &game);
	mlx_hook(game.winmlx, 17, 0L, (void *)exit_game, &game);
	mlx_loop(game.initmlx);
	return (0);
}