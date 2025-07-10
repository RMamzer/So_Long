/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_visual_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:44:01 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/10 15:29:32 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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

void	display_moves_text(t_game *game)
{
	game->img->text_str = mlx_put_string(game->mlx, " NUMBER OF MOVES:",
			0, game->height * SIZE);
	if (!game->img->text_str)
		error_exit("Failed to write text into the screen", game);
	display_moves_num(game);
}

void	display_moves_num(t_game *game)
{
	char	*num_str;

	if (game->img->text_num != NULL)
		mlx_delete_image(game->mlx, game->img->text_num);
	num_str = ft_itoa(game->steps);
	if (!num_str)
		error_exit("Itoa conversion failed", game);
	game->img->text_num = mlx_put_string (game->mlx, num_str,
			170, game->height * SIZE);
	if (!game->img->text_num)
	{
		free (num_str);
		error_exit("Failed to write number of steps into the screen", game);
	}
	free(num_str);
}

void	free_bonus_img(t_game *game, t_img *img)
{
	if (img->enemy[0] != NULL)
		mlx_delete_image(game->mlx, img->enemy[0]);
	if (img->enemy[1] != NULL)
		mlx_delete_image(game->mlx, img->enemy[1]);
	if (img->enemy[2] != NULL)
		mlx_delete_image(game->mlx, img->enemy[2]);
	if (img->text_str != NULL)
		mlx_delete_image(game->mlx, img->text_str);
	if (img->text_num != NULL)
		mlx_delete_image(game->mlx, img->text_num);
	if (img->pickup_right != NULL)
		mlx_delete_image(game->mlx, img->pickup_right);
	if (img->pickup_left != NULL)
		mlx_delete_image(game->mlx, img->pickup_left);
	if (img->pickup_t_left != NULL)
		mlx_delete_texture(img->pickup_t_left);
	if (img->pickup_t_right != NULL)
		mlx_delete_texture(img->pickup_t_right);
	if (img->exit_closed != NULL)
		mlx_delete_image(game->mlx, img->exit_closed);
}
