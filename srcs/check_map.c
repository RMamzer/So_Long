/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:13:20 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/04 15:17:58 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void check_extension(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (len <=4 || ft_strncmp(file_name + len - 4, ".ber", 4)!= 0)
		error_exit("Only .bers ʕ•ᴥ•ʔ can pass", NULL);
}

void	check_empty_lines(t_game *game)
{
	char	*map_str;
	int	i;


	map_str = game->map_str;
	i = 0;
	if(map_str[i]== '\n')
		error_exit("Empty line detected before the map", game);
	while (map_str[++i])
	{
		if (map_str[i] == '\n' && map_str[i+1] == '\n')
			error_exit("Empty line detected inside the map", game);
	}
	if(map_str[i-1]== '\n')
		error_exit("Empty line detected after the map", game);
}


void	check_map_objects(t_game *game)
{
	int		player;
	int		exit;
	char	*map_str;
	int		collectible;

	player = 0;
	exit = 0;
	collectible = 0;
	map_str = game->map_str;
	while (*map_str)
	{
		if (*map_str !='0' && *map_str !='1' && *map_str !='C' &&
			*map_str !='E' && *map_str !='P' && *map_str !='\n')
			error_exit("Incorrect objects detected on the map", game);
		if (*map_str == 'C')
			collectible++;
		else if (*map_str == 'E')
			exit++;
		else if (*map_str == 'P')
			player++;
		map_str++;
	}
	if (player != 1 || exit != 1 ||collectible < 1)
		error_exit("Map requires 1 start, 1 exit and collectibles", game);
}

void	check_map_shape(t_game *game)
{
	size_t 	length;
	size_t 	height;
	char	**map;

	map = game->map;
	length = ft_strlen(map[0]);
	height = 0;
	while(map[height] != NULL)
	{
		if (length != ft_strlen(map[height]))
			error_exit("Map must be rectangular", game);
		height ++;
	}
	game->length = length;
	game->height = height;
}


void	check_walls(t_game	*game)
{

	size_t	l;
	size_t	h;

	h = 0;
	while (game->map[h] != NULL)
	{
		if (h == 0 || h == game->height - 1)
		{
			l = 0;
			while(game->map[h][l])
			{
				if (game->map[h][l] != '1')
					error_exit("Map is not surrounded with walls", game);
				l++;
			}
		}
		else if (game->map[h][0] != '1' || game->map[h][game->length - 1] != '1')
			error_exit("Map is not surrounded with walls", game);
		h++;
	}
}
