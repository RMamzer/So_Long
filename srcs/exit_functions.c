/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:35:32 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/04 16:20:31 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/so_long.h"


void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}
void	free_img(t_game *game, t_img  *img)
{
	if (img != NULL)
	{
		if (img->background != NULL)
			mlx_delete_image(game->mlx, img->background);
		if (img->collectible != NULL)
			mlx_delete_image(game->mlx, img->collectible);
		if (img->exit != NULL)
			mlx_delete_image(game->mlx, img->exit);
		if (img->player != NULL)
			mlx_delete_image(game->mlx, img->player);
		if (img->wall != NULL)
			mlx_delete_image(game->mlx, img->wall);
		free(img);

	}
}

void	error_exit(char *msg, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);

	if (game != NULL)
	{
		if (game->map_str != NULL)
			free (game->map_str);
		if (game->map != NULL)
			free_map (game->map);
		if(game->img != NULL)
			free_img(game, game->img);
		if (game->mlx != NULL)
			mlx_terminate(game->mlx);
		free(game);
	}
	exit (1);
}

