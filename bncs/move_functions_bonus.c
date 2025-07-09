/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:29:38 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/09 17:58:36 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"


void	create_player_direction(t_game *game, t_img *img, size_t x, size_t y)
{
	int32_t check;

	check = 0;
	if (img->direction == 'd')
	{
		img->player_right = mlx_texture_to_image(game ->mlx, img->player_t_right);
		if (!img->player_right)
			error_exit("Failed to update player direction", game);
		mlx_resize_image(img->player_right, SIZE, SIZE);
		check = mlx_image_to_window(game->mlx, img->player_right, x * SIZE, y * SIZE);
	}
	else
	{
		img->player_left = mlx_texture_to_image(game ->mlx, img->player_t_left);
		if (!img->player_left)
			error_exit("Failed to update player direction", game);
		mlx_resize_image(img->player_left, SIZE, SIZE);
		check = mlx_image_to_window(game->mlx, img->player_left, x * SIZE, y * SIZE);
	}
	if (check < 0)
 		error_exit("Failed to redraw player image", game);
	game->steps++;
}

void	conduct_move(t_game	*game, char c)
{
	if (c == 'w' && game->map[game->plr_y - 1][game->plr_x] != '1')
	{
		game->plr_y--;
		move_player_image(game, game->img);
	}
	else if (c == 's' && game->map[game->plr_y + 1][game->plr_x] != '1')
	{
		game->plr_y++;
		move_player_image(game, game->img);
	}
	else if (c == 'd' && game->map[game->plr_y][game->plr_x + 1] != '1')
	{
		game->img->direction = 'd';
		game->plr_x++;
		move_player_image(game, game->img);
	}
	else if (c == 'a' && game->map[game->plr_y][game->plr_x - 1] != '1')
	{
		game->img->direction = 'a';
		game->plr_x--;
		move_player_image(game, game->img);
	}
	update_map(game, game->map);
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		conduct_move(game, 'w');
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		conduct_move(game, 'd');
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		conduct_move(game, 'a');
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		conduct_move(game, 's');
}

void	update_map(t_game *game, char **map)
{
	if (map[game->plr_y][game->plr_x] == 'M')
	{
		mlx_close_window(game->mlx);
		ft_printf("Oh NOOOO... The ghost got you :(. You have lost\n");
		success_exit(NULL, game);
	}
	if (map[game->plr_y][game->plr_x] == 'C')
		pickup_collectible(game, map, game->img->collectible);
	if (game->collect == 0 && game->img->exit_closed)
		update_exit(game, game->img, game->exit_x, game->exit_y);
	if (map[game->plr_y][game->plr_x] == 'E' && game->collect == 0)
	{
		mlx_close_window(game->mlx);
		success_exit("Congratulations, your total steps are:", game);
	}
}
