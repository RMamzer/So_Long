/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:39:55 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/01 19:54:08 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H


#include "MLX42/MLX42.h"
#include <stdbool.h>
#include "libft.h"
#include <fcntl.h> // open nd close, etc
//DELETE LATER, FOR PRINTF TESTING;
#include <stdio.h>

typedef struct s_game
{
	char	*map_str;
	char	**map;

	size_t	length;
	size_t	height;
	size_t	collect;
	size_t	plr_x;
	size_t	plr_y;
	size_t	exit_x;
	size_t	exit_y;
	bool 	exit_found;
} t_game;

//main
int main(int argc, char **argv);
char	*so_strjoin(char *s1, char *s2);
char	*get_map_str(char *file_name, t_game *game);
void	init_game(t_game *game);

//check_map
void	check_extension(char *file_name);
void	check_empty_lines(t_game *game);
void	check_map_objects(t_game *game);
void	check_map_shape(t_game *game);
void	check_walls(t_game	*game);


//exit_functions
void	free_map(char **map);
void	error_exit(char *msg, t_game *game);
#endif
