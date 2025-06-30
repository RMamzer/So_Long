/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:13:20 by rmamzer           #+#    #+#             */
/*   Updated: 2025/06/30 12:37:03 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void check_extension(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (len <=4 || ft_strncmp(file_name + len - 4, ".ber", 4)!= 0)
		error_exit("Only .bers ʕ•ᴥ•ʔ can pass");

}
bool	check_map_objects(char *map_str)
{
	int	player;
	int	collect;
	int	exit;

	player = 0;
	collect = 0;
	exit = 0;
	while (*map_str)
	{
		if (*map_str !='0' && *map_str !='1' && *map_str !='C' &&
			*map_str !='E' && *map_str !='P' && *map_str !='\n')
			return(false);
		if (*map_str == 'C')
			collect++;
		else if (*map_str == 'E')
			exit++;
		else if (*map_str == 'P')
			player++;
		map_str++;
	}
	if (player != 1 || exit != 1 ||collect < 1)
		return (false);
	return (true);
}


// void	check_map_shape(char *map_str)
// {
// 	int length;
// 	int height;

// 	length = ft_strlen_modified(*map_str);
// 	height = 0;
// 	while(*map_str)
// 	{
// 		if (*map_str == '\n')
// 	}

// }
