/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:29:38 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/08 16:56:25 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	conduct_move(t_game	*game, char c)
{
	if (c == 'w' && game->map[game->plr_y - 1][game->plr_x] != '1')
	{
		game->plr_y--;
		move_player_image(game, game->img, game->plr_x, game->plr_y);
	}
	else if (c == 's' && game->map[game->plr_y + 1][game->plr_x] != '1')
	{
		game->plr_y++;
		move_player_image(game, game->img, game->plr_x, game->plr_y);
	}
	else if (c == 'd' && game->map[game->plr_y][game->plr_x + 1] != '1')
	{
		game->plr_x++;
		move_player_image(game, game->img, game->plr_x, game->plr_y);
	}
	else if (c == 'a' && game->map[game->plr_y][game->plr_x - 1] != '1')
	{
		game->plr_x--;
		move_player_image(game, game->img, game->plr_x, game->plr_y);
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
	if (map[game->plr_y][game->plr_x] == 'C')
		pickup_collectible(game, map, game->img->collectible);
	if (map[game->plr_y][game->plr_x] == 'E' && game->collect == 0)
	{
		mlx_close_window(game->mlx);
		success_exit("Congratulations, your total steps are:", game);
	}
}
