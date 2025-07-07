/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:36:59 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/07 16:29:13 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*so_strjoin(char *s1, char *s2)
{
	char	*joinedstr;
	size_t	str1_l;
	size_t	str2_l;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		str1_l = 0;
	else
		str1_l = ft_strlen(s1);
	str2_l = ft_strlen(s2);
	joinedstr = malloc(str1_l + str2_l + 1);
	if (!joinedstr)
	{
		free (s1);
		free (s2);
		return (NULL);
	}
	ft_memcpy(joinedstr, s1, str1_l);
	ft_memcpy(joinedstr + str1_l, s2, str2_l);
	joinedstr[str1_l + str2_l] = '\0';
	free (s1);
	free (s2);
	return (joinedstr);
}

char	*get_map_str(char *file_name, t_game *game)
{
	int		fd;
	char	*next_line;
	char	*map_str;

	map_str = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open the map 🗺️", game);
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		map_str = so_strjoin(map_str, next_line);
		if (!map_str)
		{
			close(fd);
			error_exit("Malloc function misfunction", game);
		}
	}
	close(fd);
	if (map_str == NULL)
		error_exit("Empty file", game);
	return (map_str);
}

void	find_objects(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
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
			else if (game->map[y][x] == 'C')
				game->collect++;
			x++;
		}
		y++;
	}
}

void	flood_fill(t_game *copy, size_t x, size_t y)
{
	if (copy->collect == 0 && copy->exit_found == true)
		return ;
	if (copy->map[y][x] == '1' || copy->map[y][x] == '~')
		return ;
	if (copy->map[y][x] == 'E')
		copy->exit_found = true;
	if (copy->map[y][x] == 'C')
		copy->collect--;
	copy->map[y][x] = '~';
	flood_fill(copy, x + 1, y);
	flood_fill(copy, x - 1, y);
	flood_fill(copy, x, y + 1);
	flood_fill(copy, x, y - 1);
}

void	check_route(t_game *game)
{
	t_game	copy;

	find_objects(game);
	copy.map = ft_split(game->map_str, '\n');
	if (!copy.map)
		error_exit("ft_slit malloc broke during map  copying", game);
	copy.height = game->height;
	copy.length = game->length;
	copy.collect = game->collect;
	copy.plr_x = game->plr_x;
	copy.plr_y = game->plr_y;
	copy.exit_found = false;
	flood_fill(&copy, copy.plr_x, copy.plr_y);
	if (copy.collect != 0 || copy.exit_found == false)
	{
		free_map(copy.map);
		error_exit("No valid path", game);
	}
	free_map(copy.map);
}
