/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_enemy_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:35:20 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/10 15:21:01 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	get_enemy(t_img *img, t_game *game)
{
	mlx_texture_t	*png;
	int				i;
	const char		*path[3];

	i = 0;
	path[0] = "./imgs/enemy.png";
	path[1] = "./imgs/enemy_1.png";
	path[2] = "./imgs/enemy_2.png";
	while (i < 3)
	{
		png = mlx_load_png(path[i]);
		if (!png)
			error_exit("Error during loading enemy image", game);
		img->enemy[i] = mlx_texture_to_image(game->mlx, png);
		mlx_delete_texture(png);
		if (!img->enemy[i])
			error_exit("Error during converting enemy image", game);
		mlx_resize_image(img->enemy[i], SIZE, SIZE);
		i++;
	}
}

void	enemy_hook(void *temp)
{
	t_game	*game;
	double	frame_l;
	double	current_time;

	game = temp;
	frame_l = 0.2;
	current_time = mlx_get_time();
	if (current_time - game->img->last_enemy_time >= frame_l)
	{
		game->img->enemy_frame = (game->img->enemy_frame + 1) % 3;
		game->img->last_enemy_time = current_time;
		game->img->enemy[0]->enabled = false;
		game->img->enemy[1]->enabled = false;
		game->img->enemy[2]->enabled = false;
		game->img->enemy[game->img->enemy_frame]->enabled = true;
	}
}

void	place_enemies(t_game *game, t_img *img, size_t x, size_t y)
{
	int32_t	check;
	int		i;

	check = 0;
	i = 0;
	while (i < 3)
	{
		check = mlx_image_to_window(game->mlx, img->enemy[i],
				x * SIZE, y * SIZE);
		if (check < 0)
			error_exit("Could not place an enemy", game);
		i++;
	}
	img->enemy[0]->enabled = true;
	img->enemy[1]->enabled = false;
	img->enemy[2]->enabled = false;
}

void	create_pickup_image(t_game *game, t_img *img, size_t x, size_t y)
{
	int32_t	check;

	check = 0;
	if (img->direction == 'd')
	{
		img->pickup_right = mlx_texture_to_image(game->mlx,
				img->pickup_t_right);
		if (!img->pickup_right)
			error_exit("Failed to update pickup direction", game);
		mlx_resize_image(img->pickup_right, SIZE, SIZE);
		check = mlx_image_to_window(game->mlx,
				img->pickup_right, x * SIZE, y * SIZE);
	}
	else
	{
		img->pickup_left = mlx_texture_to_image(game->mlx, img->pickup_t_left);
		if (!img->pickup_left)
			error_exit("Failed to update pickup direction", game);
		mlx_resize_image(img->pickup_left, SIZE, SIZE);
		check = mlx_image_to_window(game->mlx,
				img->pickup_left, x * SIZE, y * SIZE);
	}
	if (check < 0)
		error_exit("Failed to draw pickup image", game);
	img->pickup_needed = false;
}
