/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_visuals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:02:10 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/07 16:34:35 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	img->player_t = mlx_load_png("./imgs/player.png");
	if (!(img->player_t))
		error_exit("Error during loading player image", game);
	img->player = mlx_texture_to_image(game->mlx, img->player_t);
	if (!img->player)
		error_exit("Error during converting player image", game);
	mlx_resize_image(img->player, SIZE, SIZE);
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
		error_exit("Error during loading wall./	 image", game);
	img->exit = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->wall)
		error_exit("Error during converting wall image", game);
	mlx_resize_image(img->exit, SIZE, SIZE);
}
