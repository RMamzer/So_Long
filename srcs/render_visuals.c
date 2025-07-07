/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_visuals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:35:01 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/07 16:49:34 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
}

void	place_object(t_game *game, size_t x, size_t y)
{
	int32_t	check;

	check = 0;
	if (game->map[y][x] == 'P')
		check = mlx_image_to_window(game->mlx, game->img->player,
				x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'C')
		check = mlx_image_to_window(game->mlx, game->img->collectible,
				x * SIZE + SIZE / 4, y * SIZE + SIZE / 3);
	else if (game->map[y][x] == '1')
		check = mlx_image_to_window(game->mlx, game->img->wall,
				x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'E')
		check = mlx_image_to_window(game->mlx, game->img->exit,
				x * SIZE, y * SIZE);
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
			if (y == game->plr_y && x == game->plr_x)
			{
				if (coll->instances[i].enabled == false)
					return ;
				coll->instances[i].enabled = false;
				game->collect--;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	move_player_image(t_game *game, t_img *img, size_t x, size_t y)
{
	int32_t	check;

	mlx_delete_image(game->mlx, img->player);
	img->player = mlx_texture_to_image(game->mlx, img->player_t);
	if (!img->player)
		error_exit("Failed to update player image", game);
	mlx_resize_image(img->player, SIZE, SIZE);
	check = mlx_image_to_window(game->mlx, img->player, x * SIZE, y * SIZE);
	if (check < 0)
		error_exit("Failed to redraw player image", game);
	game->steps++;
	ft_printf("current steps: %d\n", game->steps);
}
