/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_visuals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:35:01 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/10 15:27:44 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	render_map(t_game *game)
{
	size_t	x;
	size_t	y;
	int32_t	check;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->length)
		{
			check = 0;
			check = mlx_image_to_window(game->mlx, game->img->background,
					x * SIZE, y * SIZE);
			if (check < 0)
				error_exit("Could not fill the background", game);
			place_object(game, x, y);
			x++;
		}
		y++;
	}
	display_moves_text(game);
}

void	place_object(t_game *game, size_t x, size_t y)
{
	int32_t	check;

	check = 0;
	if (game->map[y][x] == 'P')
		check = mlx_image_to_window(game->mlx, game->img->player_right,
				x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'C')
		check = mlx_image_to_window(game->mlx, game->img->collectible,
				x * SIZE + SIZE / 4, y * SIZE + SIZE / 3);
	else if (game->map[y][x] == '1')
		check = mlx_image_to_window(game->mlx, game->img->wall,
				x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'E')
		check = mlx_image_to_window(game->mlx, game->img->exit_closed,
				x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'M')
		place_enemies(game, game->img, x, y);
	if (check < 0)
		error_exit("Could not place the object", game);
}

void	pickup_collectible(t_game *game, char **map, mlx_image_t *coll)
{
	size_t	x;
	size_t	y;
	int		i;

	i = -1;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->length)
		{
			if (map[y][x] == 'C')
				i++;
			if (y == game->plr_y && x == game->plr_x
				&& coll->instances[i].enabled == true)
			{
				coll->instances[i].enabled = false;
				game->collect--;
				game->img->pickup_needed = true;
				move_player_image(game, game->img);
			}
			x++;
		}
		y++;
	}
}

void	update_exit(t_game *game, t_img *img, size_t x, size_t y)
{
	int32_t	check;

	check = 0;
	if (img->exit_closed)
	{
		mlx_delete_image(game->mlx, img->exit_closed);
		check = mlx_image_to_window(game->mlx, img->exit, x * SIZE, y * SIZE);
		if (check < 0)
			error_exit("Failed to update exit image", game);
	}
}
