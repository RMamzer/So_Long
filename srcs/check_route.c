/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:36:59 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/02 18:43:02 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


void	init_game(t_game *game)
{
	find_objects (game);
}

void	find_objects(t_game *game)
{
	size_t x;
	size_t y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while(game->map[y][x])
		{
			if (game->map[y][x] == 'P' )
			{
				game->plr_x = x;
				game->plr_y = y;
			}
			else if (game->map[y][x] == 'E' )
			{
				game->exit_x = x;
				game->exit_y = y;
			}
			else if (game->map[y][x]== 'C')
				game->collect++;
			x++;
		}
		y++;
	}
}
void	flood_fill(t_game *copy, size_t x, size_t y)
{
	if (copy->collect == 0 && copy->exit_found == true)
		return;
	if (copy->map[y][x] == '1' ||copy->map[y][x] == '~')
		return;
	if(copy->map[y][x] == 'E')
		copy->exit_found = true;
	if(copy->map[y][x] == 'C')
		copy->collect--;
	copy->map[y][x] = '~';
	//print_args(copy->map);// <--------------------------------------DELETE LATER
	flood_fill(copy, x + 1, y);
	flood_fill(copy, x - 1, y);
	flood_fill(copy, x, y + 1);
	flood_fill(copy, x, y - 1);
}

void	check_route(t_game *game)
{
	t_game	copy;

	init_game(game);
	copy.map = ft_split(game->map_str,'\n');
	if (!copy.map)
		error_exit("ft_slit malloc broke during map  copying", game);
	copy.height = game->height;
	copy.length = game->length;
	copy.collect= game->collect;
	copy.plr_x = game->plr_x;
	copy.plr_y = game->plr_y;
	copy.exit_found = false;
	// print_game_object_data(game);
	// print_game_object_data(&copy);

	flood_fill(&copy, copy.plr_x, copy.plr_y);
	if (copy.collect != 0 || copy.exit_found == false)
	{
		free_map(copy.map);
		error_exit("No valid path", game);
	}
	free_map(copy.map);
}
