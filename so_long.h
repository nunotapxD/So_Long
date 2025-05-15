/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntomas-a <ntomas-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:28:10 by ntomas-a          #+#    #+#             */
/*   Updated: 2025/05/15 23:28:10 by ntomas-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "Libft/libft.h"
# include "Printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		x;
	int		y;
	int		endian;
}			t_data;

typedef struct s_game
{
	char **map; // map[y][x]
	int		map_width;
	int		map_height;

	int moves_count;   // moves_count = 0
	int collect_count; // collect_count = 0
	int exit_count;    // exit_count = 0
	int player_count;  // player_count = 0

	t_data	img;
	t_data	wall;
	t_data	player;
	t_data	exit;
	t_data	collect;
	t_data	floor;

	int		player_x;
	int		player_y;

	int		exit_x;
	int		exit_y;

	void	*initmlx;
	void	*winmlx;
}			t_game;

/* --- Checker Functions --- */
void		check_ac(int ac);
int			check_fd(char *filepath);
int			check_map_size(t_game *game);
void		check_errors(t_game *game);

/* --- Image Functions --- */
t_data		create_img(char *path, t_game *game);
void		put_images(t_game *game);
void		init_images(t_game *game);
void		choose_image(t_game *game, int y, int x);
void		refresh_graphics_player(t_game *game, int x_pos, int y_pos,
				char flag);

/* --- Map Functions --- */
int			check_limits(t_game *game);
int			save_map_line(t_game *game, char *line);
void		save_coords(t_game *game, int y, int x, int flag);
int			read_chars(t_game *game);
int			read_map(t_game *game, char *filepath);

/* --- Control Functions --- */
void		move_w(t_game *game, int key);
void		move_a(t_game *game, int key);
void		move_s(t_game *game, int key);
void		move_d(t_game *game, int key);
int			controls(int key, t_game *game);

/* --- Utils Functions --- */
void		destroy_images(t_game *game);
void		ft_free(char **map);
void		exit_game(t_game *game);
void		to_complete(t_game *game, int x, int y);
void		errors_map(t_game *game);

int			handle_ff(t_game *game);
void		flod_fill(char **map, int x, int y, int *count);

#endif