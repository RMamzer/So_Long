/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:35:32 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/01 14:36:12 by rmamzer          ###   ########.fr       */
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
		free(game);
	}
	exit (1);
}
