/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_visuals_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:02:10 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/10 11:49:48 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	get_background(t_img *img, t_game *game)
{
	mlx_texture_t	*png;

	png = mlx_load_png("./imgs/background.png");
	if (!png)
		error_exit("Error during loading background image", game);
	img->background = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->background)
		error_exit("Error during converting background image", game);
	mlx_resize_image(img->background, SIZE, SIZE);
}

void	get_player(t_img *img, t_game *game)
{
	img->player_t_right = mlx_load_png("./imgs/player.png");
	if (!(img->player_t_right))
		error_exit("Error during loading player image", game);
	img->player_right = mlx_texture_to_image(game->mlx, img->player_t_right);
	if (!img->player_right)
		error_exit("Error during converting player image", game);
	img->player_t_left = mlx_load_png("./imgs/player_left.png");
	if (!(img->player_t_left))
		error_exit("Error during loading player image", game);
	img->player_left = mlx_texture_to_image(game->mlx, img->player_t_left);
	if (!img->player_left)
		error_exit("Error during converting player image", game);
	mlx_resize_image(img->player_right, SIZE, SIZE);
}

void	get_collectible(t_img *img, t_game *game)
{
	mlx_texture_t	*png;

	png = mlx_load_png("./imgs/collectible.png");
	if (!png)
		error_exit("Error during loading collectible image", game);
	img->collectible = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->collectible)
		error_exit("Error during converting collectible image", game);
	mlx_resize_image(img->collectible, SIZE / 2, SIZE / 2);
}

void	get_wall(t_img *img, t_game *game)
{
	mlx_texture_t	*png;

	png = mlx_load_png("./imgs/wall.png");
	if (!png)
		error_exit("Error during loading wall image", game);
	img->wall = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->wall)
		error_exit("Error during converting wall image", game);
	mlx_resize_image(img->wall, SIZE, SIZE);
}

void	get_exit(t_img *img, t_game *game)
{
	mlx_texture_t	*png;

	png = mlx_load_png("./imgs/exit.png");
	if (!png)
		error_exit("Error during loading exit image", game);
	img->exit = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->exit)
		error_exit("Error during converting exit image", game);
	mlx_resize_image(img->exit, SIZE, SIZE);
	png = mlx_load_png("./imgs/exit_closed.png");
	if (!png)
		error_exit("Error during loading closed exit image", game);
	img->exit_closed= mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->exit_closed)
		error_exit("Error during converting closed exit image", game);
	mlx_resize_image(img->exit_closed, SIZE, SIZE);
}

void	get_enemy(t_img *img, t_game *game)
{
	mlx_texture_t	*png;
	int i;
	const char *path[3];

	i = 0;
	path[0] = "./imgs/enemy.png";
	path[1]  = "./imgs/enemy_1.png";
	path[2]  = "./imgs/enemy_2.png";
	while (i<3)
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


void	get_pickup(t_img *img, t_game *game)
{
	img->pickup_t_right = mlx_load_png("./imgs/pickup_right.png");
	if (!(img->pickup_t_right))
		error_exit("Error during loading player image", game);
	img->pickup_right = mlx_texture_to_image(game->mlx, img->pickup_t_right);
	if (!img->pickup_right)
		error_exit("Error during converting player image", game);
	img->pickup_t_left = mlx_load_png("./imgs/pickup_left.png");
	if (!(img->pickup_t_left))
		error_exit("Error during loading player image", game);
	img->pickup_left = mlx_texture_to_image(game->mlx, img->pickup_t_left);
	if (!img->pickup_left)
		error_exit("Error during converting player image", game);
	mlx_resize_image(img->pickup_right, SIZE, SIZE);
	mlx_resize_image(img->pickup_left, SIZE, SIZE);
}
